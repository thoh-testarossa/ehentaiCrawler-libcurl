#pragma once

#include "config.h"

#include "pageAnalyzer.h"

class picPageAnalyzer : public pageAnalyzer
{
public:
    picPageAnalyzer(const string &inputPage);
    string getNextPageURL();
    string getPrevPageURL();
    string getLossyPicSourceURL();
    string getOriginalPicSourceURL();
    int getCurrentPageNumber();
};
