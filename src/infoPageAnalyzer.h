#pragma once

#include "config.h"

#include "pageAnalyzer.h"

class infoPageAnalyzer : public pageAnalyzer
{
public:
    infoPageAnalyzer(const std::string &inputPage);
    std::string getComicOriginalName();
    std::string getComicTranslatedName();
    std::string getFirstPicPageURL();
    int getTotalPageNumber();
};
