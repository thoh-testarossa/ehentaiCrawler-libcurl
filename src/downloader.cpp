#include "downloader.h"

#include <ctime>
#include <cstdlib>

#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <sstream>

#include "curl/curl.h"

int downloader::isInit = 0;

void downloader::curlInit(const std::vector<std::string> &originalURLSet)
{
    if(this->isInit == 0)
        curl_global_init(CURL_GLOBAL_ALL);
    this->isInit++;
    this->setOriginalURLSet(originalURLSet);
    this->downloadURLSet = std::vector<std::string>();
    this->downloadResultSet = std::map<std::string, std::string>();
}

void downloader::curlClean()
{
    this->isInit--;
    if(this->isInit == 0)
        curl_global_cleanup();
    this->originalURLSet.clear();
    this->downloadURLSet.clear();
    this->downloadResultSet.clear();
}

downloader::downloader()
{
    this->originalURLSet = std::vector<std::string>();
    this->downloadURLSet = std::vector<std::string>();
    this->downloadResultSet = std::map<std::string, std::string>();
}

void downloader::setOriginalURLSet(const std::vector<std::string> &originalURLSet)
{
    this->originalURLSet = originalURLSet;
}

//This filter is based on "OR" mechanism
std::vector<std::string> downloader::findURLwithPattern(const std::vector<std::string> &patternSet, int filterMode)
{
    std::vector<std::string> result = std::vector<std::string>();
    if(filterMode == FILTERMODE_NEW) result = this->originalURLSet;
    else if(filterMode == FILTERMODE_ADD) result = this->downloadURLSet;
    for(std::vector<std::string>::iterator url_iter = result.begin(); url_iter != result.end(); url_iter++)
    {
        std::vector<std::string>::const_iterator pattern_iter;
        for(pattern_iter = patternSet.begin(); pattern_iter != patternSet.end(); pattern_iter++)
        {
            if(this->doesURLHavePattern(*url_iter, *pattern_iter))
                break;
        }
        if(!patternSet.empty() && pattern_iter == patternSet.end()) result.erase(url_iter);
    }
    this->downloadURLSet = result;
    return result;
}

bool downloader::doesURLHavePattern(const std::string &url, const std::string &pattern)
{
    if(url.find(pattern) != std::string::npos) return true;
    else return false;
}

//A multiple thread method(downloadURLInSetByThread called)
//Notice: thread constructor only accepts value parameters and it will reject reference parameters
void downloader::downloadAllURLsInSet(int threadNum, const std::string &path)
{
    std::vector<std::map<std::string, std::string>> tmpResultSet = std::vector<std::map<std::string, std::string>>();
    for(int i = 0; i < threadNum; i++)
        tmpResultSet.push_back(std::map<std::string, std::string>());

    std::vector<std::thread> threadPool = std::vector<std::thread>();
    for(int i = 0; i < threadNum; i++)
        threadPool.push_back(std::thread(&downloader::downloadURLInSetByThread, this, i, threadNum, path, &tmpResultSet[i]));

    bool *isJoint = new bool[threadNum];
    for(int i = 0; i < threadNum; i++) isJoint[i] = false;
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bool allThreadChk = true;
        for(int i = 0; i < threadNum; i++)
        {
            if(!isJoint[i])
            {
                if(threadPool[i].joinable())
                {
                    threadPool[i].join();
                    isJoint[i] = true;
                }
            }
            allThreadChk &= isJoint[i];
        }
        if(allThreadChk) break;
    }
    free(isJoint);

    for(int i = 0; i < threadNum; i++)
        this->downloadResultSet.insert(tmpResultSet[i].begin(), tmpResultSet[i].end());
}

//Download the content from the url this->downloadURLSet[pos]
//libcurl used here
std::string downloader::downloadURLInSetAtPos(int pos, const std::string &path)
{
    CURL *curl = curl_easy_init();

    memBlockStruc buf = {0, 1, nullptr};

    curl_easy_setopt(curl, CURLOPT_URL, this->downloadURLSet[pos].c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)(&buf));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->fetchDownloadedData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::string content = std::string("");

    for(int i = 0; i < buf.realSize; i++)
        content += buf.memBlock[i];

    free(buf.memBlock);

    return content;
}

//One thread generate one part of download result by making a reasonable file name and calling downloadURLInSetAtPos()
void downloader::downloadURLInSetByThread(int threadNo, int threadNum, const std::string &path, std::map<std::string, std::string> *tmpResult)
{
    for(int i = threadNo; i < this->downloadURLSet.size(); i += threadNum)
    {
        std::cout << "Page " << i << " begin" << std::endl;
        //File name part
        std::string tarFileName = this->getFileNameFromURL(this->downloadURLSet.at(i));
        std::string fileName = path + tarFileName;

        //File content part
        std::string fileContent = std::string("");
        fileContent += this->downloadURLInSetAtPos(i, path);

        tmpResult->insert(std::pair<std::string, std::string> (fileName, fileContent));
        std::cout << "Page " << i << " end" << std::endl;
    }
}

//We assume that *stream is a external memBlockStruc pointer which we will push the downloaded data into it
size_t downloader::fetchDownloadedData(char *ptr, size_t size, size_t nmemb, void *stream)
{
    memBlockStruc *mem = (memBlockStruc *)stream;

    if(mem->memBlock == nullptr) mem->memBlock = (char *)malloc(mem->allocSize);
    if(mem->memBlock == nullptr) return -1;
    while(mem->realSize + size * nmemb > mem->allocSize)
    {
        mem->allocSize <<= 1;
        mem->memBlock = (char *)realloc(mem->memBlock, mem->allocSize);
    }

    memcpy(&(mem->memBlock[mem->realSize]), ptr, size * nmemb);
    mem->realSize += size * nmemb;
    return size * nmemb;
}

std::map<std::string, std::string> downloader::returnDownloadResultSet()
{
    return this->downloadResultSet;
}

std::string downloader::getFileNameFromURL(const std::string &downloadURL)
{
    std::string result = std::string("");
    for(int i = downloadURL.length() - 1; i >= 0; i--)
    {
        if(downloadURL[i] == '/' && result != std::string("")) break;
        result += downloadURL[i];
    }
    std::reverse(result.begin(), result.end());
    return result;
}
