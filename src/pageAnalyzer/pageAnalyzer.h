#pragma once

#include "../include/config.h"

#define GETMODE_ALL 17
#define GETMODE_PART 18

class pageAnalyzer
{
public:
    pageAnalyzer(const std::string &inputPage);
    std::string getInfoFromContent(const std::string &keyToFindTarStr, int offset, int getMode, const std::string &keyToFindPos, char endChar);
protected:
    void decomposePageContent();
    std::string inputPage;
    std::vector<std::string> pageContent;
};
