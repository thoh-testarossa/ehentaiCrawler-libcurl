#ifndef COMMON_H
#define COMMON_H

#include "commonHeader.h"

#endif

#ifndef DOWNLOADER_H
#define DOWNLOADER_H

using namespace std;

#define FILTERMODE_NEW 29
#define FILTERMODE_ADD 30

class downloader
{
public:
    downloader(const vector<string> &originalURLSet);
    vector<string> findURLwithPattern(const vector<string> &patternSet, int filterMode);
    void downloadAllURLsInSet(const string &path);
    //test function!
    void downloadRandomURLInSet(const string &path);
protected:
    bool doesURLHavePattern(const string &url, const string &pattern);
    void downloadURLInSetAtPos(int pos, const string &path);
    vector<string> originalURLSet;
    vector<string> downloadURLSet;
};

#endif
