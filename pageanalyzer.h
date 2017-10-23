#ifndef COMMON_H
#define COMMON_H

#include "commonHeader.h"

#endif // COMMON_H

#ifndef PAGEANALYZER_H
#define PAGEANALYZER_H

using namespace std;

class infoPageAnalyzer
{
public:
    infoPageAnalyzer(const string &inputPage);
    string getComicOriginalName();
    string getComicTranslatedName();
    string getFirstPicPageURL();
    int getTotalPageNumber();
private:
    string inputPage;
    vector<string> pageContent;
    void decomposePageContent();
};

class picPageAnalyzer
{
public:
    picPageAnalyzer(const string &inputPage);
    string getNextPageURL();
    string getPrevPageURL();
    string getLossyPicSourceURL();
    string getOriginalPicSourceURL();
    int getCurrentPageNumber();
private:
    string inputPage;
    vector<string> pageContent;
    void decomposePageContent();
};

#endif // PAGEANALYZER_H
