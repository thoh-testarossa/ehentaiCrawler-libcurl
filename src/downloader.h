#pragma once

#include "config.h"

#define FILTERMODE_NEW 29
#define FILTERMODE_ADD 30

typedef struct memBlockStruc
{
    int realSize;
    char *memBlock;
}memBlockStruc;

class downloader
{
public:
    downloader(const std::vector<std::string> &originalURLSet);
    ~downloader();
    std::vector<std::string> findURLwithPattern(const std::vector<std::string> &patternSet, int filterMode);
    void downloadAllURLsInSet(int threadNum, const std::string &path);
    std::map<std::string, std::string> returnDownloadResultSet();
protected:
    bool doesURLHavePattern(const std::string &url, const std::string &pattern);
    std::string downloadURLInSetAtPos(int pos, const std::string &path);
    void downloadURLInSetByThread(int threadNo, int threadNum, const std::string &path, std::map<std::string, std::string> *tmpResult);

    //This function is used to fit the form of curl-write function
    size_t fetchDownloadedData(void *ptr, size_t size, size_t nmemb, void *stream);

    std::vector<std::string> originalURLSet;
    std::vector<std::string> downloadURLSet;

    std::map<std::string, std::string> downloadResultSet;
};
