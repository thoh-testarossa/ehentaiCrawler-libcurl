#pragma once

#include "config.h"

#include "pageAnalyzer.h"

class picPageAnalyzer : public pageAnalyzer
{
public:
    picPageAnalyzer(const std::string &inputPage);
    std::string getNextPageURL();
    std::string getPrevPageURL();
    std::string getLossyPicSourceURL();
    std::string getOriginalPicSourceURL();
    int getCurrentPageNumber();
};
