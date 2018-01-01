#include "downloader.h"

#include <ctime>
#include <cstdlib>


#include <fstream>
#include <thread>
#include <sstream>

#include "curl/curl.h"

downloader::downloader(const vector<string> &originalURLSet)
{
    this->originalURLSet = originalURLSet;
    curl_global_init(CURL_GLOBAL_ALL);
}

//This filter is based on "OR" mechanism
vector<string> downloader::findURLwithPattern(const vector<string> &patternSet, int filterMode)
{
    vector<string> result = vector<string>();
    if(filterMode == FILTERMODE_NEW) result = this->originalURLSet;
    else if(filterMode == FILTERMODE_ADD) result = this->downloadURLSet;
    for(vector<string>::iterator url_iter = result.begin(); url_iter != result.end(); url_iter++)
    {
        vector<string>::const_iterator pattern_iter;
        for(pattern_iter = patternSet.begin(); pattern_iter != patternSet.end(); pattern_iter++)
        {
            if(this->doesURLHavePattern(*url_iter, *pattern_iter))
                break;
        }
        if(pattern_iter == patternSet.end()) result.erase(url_iter);
    }
    this->downloadURLSet = result;
    return result;
}

bool downloader::doesURLHavePattern(const string &url, const string &pattern)
{
    if(url.find(pattern) != string::npos) return true;
    else return false;
}

void downloader::downloadAllURLsInSet(int threadNum, const string &path)
{
    //void (downloader::*f_ptr) (int, int, const std::string&) = &downloader::downloadURLInSetByThread;
    for(int i = 0; i < threadNum; i++)
    {
        std::thread thd(&downloader::downloadURLInSetByThread, this, i, threadNum, path);
        thd.join();
    }
}

void downloader::downloadURLInSetAtPos(int pos, const string &path)
{
    CURL *curl = curl_easy_init();
    std::string buf = std::string();
    curl_easy_setopt(curl, CURLOPT_URL, this->downloadURLSet.at(pos).c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&buf);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &downloader::fetchDownloadedData);
    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    std::stringstream pageNo;
    pageNo << pos;
    std::string fileName = path + pageNo.str() + std::string(".jpg");
    std::ofstream fout(fileName, ios::out | ios::binary);
    //for(int i = 0; i < buf.size(); i++) fout.write(&buf[i], 1);
    fout.write(buf.c_str(), buf.size());
    fout.close();
}

void downloader::downloadURLInSetByThread(int threadNo, int threadNum, const string &path)
{
    for(int i = threadNo; i < this->downloadURLSet.size(); i += threadNum)
        this->downloadURLInSetAtPos(i, path);
}

//We assume that *stream is a external string pointer which we will push the downloaded data into it
size_t downloader::fetchDownloadedData(void *ptr, size_t size, size_t nmemb, void *stream)
{
    std::string *str = (std::string *)stream;
    char *s_ptr = (char *)ptr;
    //Copy the content in *ptr to *stream by coping every byte
    //type "char" occupies 1 bytes for each instance
    for(int i = 0; i < size * nmemb; i++)
        *str += s_ptr[i];
    return 0;
}
