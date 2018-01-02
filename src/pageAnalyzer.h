#pragma once

#include "config.h"

using namespace std;

#define GETMODE_ALL 17
#define GETMODE_PART 18

class pageAnalyzer
{
public:
    pageAnalyzer(const string &inputPage);
    string getInfoFromContent(const string &keyToFindTarStr, int offset, int getMode, const string &keyToFindPos, char endChar);
protected:
    string inputPage;
    vector<string> pageContent;
    void decomposePageContent();
};
