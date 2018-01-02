#pragma once

#include "config.h"

using namespace std;

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
    downloader(const vector<string> &originalURLSet);
    vector<string> findURLwithPattern(const vector<string> &patternSet, int filterMode);
    void downloadAllURLsInSet(int threadNum, const string &path);
protected:
    bool doesURLHavePattern(const string &url, const string &pattern);
    void downloadURLInSetAtPos(int pos, const string &path);
    void downloadURLInSetByThread(int threadNo, int threadNum, const string &path);

    //This function is used to fit the form of curl-write function
    size_t fetchDownloadedData(void *ptr, size_t size, size_t nmemb, void *stream);

    vector<string> originalURLSet;
    vector<string> downloadURLSet;
};
