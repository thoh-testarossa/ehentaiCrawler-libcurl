#include "downloader.h"

#include <ctime>
#include <cstdlib>


#include <fstream>
#include <thread>
#include <sstream>

#include "curl/curl.h"

int downloader::isInit = 0;

void downloader::curlInit()
{
    if(this->isInit == 0)
        curl_global_init(CURL_GLOBAL_ALL);
    this->isInit++;
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

downloader::downloader(const std::vector<std::string> &originalURLSet)
{
    this->curlInit();
    this->setOriginalURLSet(originalURLSet);
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
    for(int i = 0; i < threadNum; i++)
    {
        std::thread thd(&downloader::downloadURLInSetByThread, this, i, threadNum, path, &tmpResultSet[i]);
        thd.join();
    }
    for(int i = 0; i < threadNum; i++)
        this->downloadResultSet.insert(tmpResultSet[i].begin(), tmpResultSet[i].end());
}

//Download the content from the url this->downloadURLSet[pos]
//libcurl used here
std::string downloader::downloadURLInSetAtPos(int pos, const std::string &path)
{
    CURL *curl = curl_easy_init();

    memBlockStruc buf = {0, nullptr};

    curl_easy_setopt(curl, CURLOPT_URL, this->downloadURLSet[pos].c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)(&buf));
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, this->fetchDownloadedData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::string content = std::string("");

    for(int i = 0; i < buf.realSize; i++)
        content += buf.memBlock[i];

    return content;
}

//One thread generate one part of download result by making a reasonable file name and calling downloadURLInSetAtPos()
void downloader::downloadURLInSetByThread(int threadNo, int threadNum, const std::string &path, std::map<std::string, std::string> *tmpResult)
{
    for(int i = threadNo; i < downloadURLSet.size(); i += threadNum)
    {
        //File name part
        std::string tarFileName = std::string("");
        //Use some method to get the file name here
        std::string fileName = path + tarFileName;

        //File content part
        std::string fileContent = std::string("");
        fileContent += this->downloadURLInSetAtPos(i, path);

        tmpResult->insert(std::pair<std::string, std::string> (fileName, fileContent));
    }
}

//We assume that *stream is a external memBlockStruc pointer which we will push the downloaded data into it
size_t downloader::fetchDownloadedData(char *ptr, size_t size, size_t nmemb, void *stream)
{
    memBlockStruc *mem = (memBlockStruc *)stream;

    mem->memBlock = new char [size * nmemb];
    if(mem->memBlock == nullptr) return -1;

    memcpy(&(mem->memBlock[0]), ptr, size * nmemb);
    mem->realSize = size * nmemb;
    return mem->realSize;
}

std::map<std::string, std::string> downloader::returnDownloadResultSet()
{
    return this->downloadResultSet;
}
