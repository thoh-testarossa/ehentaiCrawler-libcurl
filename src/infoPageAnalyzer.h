#pragma once

#include "config.h"

#include "pageAnalyzer.h"

class infoPageAnalyzer : public pageAnalyzer
{
public:
    infoPageAnalyzer(const string &inputPage);
    string getComicOriginalName();
    string getComicTranslatedName();
    string getFirstPicPageURL();
    int getTotalPageNumber();
};
