#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"

#endif

#ifndef PAGEANALYZER_H
#define PAGEANALYZER_H

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


#endif // PAGEANALYZER_H
