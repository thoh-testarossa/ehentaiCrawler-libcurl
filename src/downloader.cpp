#include "downloader.h"

#include <ctime>
#include <cstdlib>

downloader::downloader(const vector<string> &originalURLSet)
{
    this->originalURLSet = originalURLSet;
}

vector<string> downloader::findURLwithPattern(const vector<string> &patternSet, int filterMode)
{
    vector<string> result = vector<string>();
    vector<string> *sor;
    if(filterMode == FILTERMODE_NEW) sor = &this->originalURLSet;
    else if(filterMode == FILTERMODE_ADD) sor = &this->downloadURLSet;
    for(int i = 0; i < (*sor).size(); i++)
    {
        for(int j = 0; j < patternSet.size(); j++)
            if(doesURLHavePattern((*sor)[i], patternSet[j]))
                result.push_back((*sor)[i]);
    }
    this->downloadURLSet = result;
    return result;
}

bool downloader::doesURLHavePattern(const string &url, const string &pattern)
{
    if(url.find(pattern) != string::npos) return true;
    else return false;
}

void downloader::downloadAllURLsInSet(const string &path)
{
    for(int i = 0; i < this->downloadURLSet.size(); i++) this->downloadURLInSetAtPos(i, path);
}

void downloader::downloadRandomURLInSet(const string &path)
{
    srand(time(0));
    this->downloadURLInSetAtPos(rand()%this->downloadURLSet.size(), path);
}

void downloader::downloadURLInSetAtPos(int pos, const string &path)
{

}
