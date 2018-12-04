#include "infoPageAnalyzer.h"
#include <sstream>

infoPageAnalyzer::infoPageAnalyzer(const std::string &inputPage) : pageAnalyzer(inputPage)
{
}

std::string infoPageAnalyzer::getComicOriginalName()
{
    return this->getInfoFromContent(std::string("h1 id=\"gj\""), 1, GETMODE_ALL, std::string(""), '\0');
}

std::string infoPageAnalyzer::getComicTranslatedName()
{
    return this->getInfoFromContent(std::string("h1 id=\"gn\""), 1, GETMODE_ALL, std::string(""), '\0');
}

std::string infoPageAnalyzer::getFirstPicPageURL()
{
    return this->getInfoFromContent(std::string("img alt=\""), -2, GETMODE_PART, std::string("href=\""), '\"');
}

int infoPageAnalyzer::getTotalPageNumber()
{
    return stoi(this->getInfoFromContent(std::string("Length"), 4, GETMODE_PART, std::string(""), ' '));
}

std::string infoPageAnalyzer::getGidInString() {
    return this->getInfoFromContent(std::string("?gid="), 0, GETMODE_PART, std::string("?gid="), '&');
}

std::string infoPageAnalyzer::getPicPageURL(std::string gidString, int picPageNum) {
    std::stringstream ss = std::stringstream();
    ss << picPageNum;
    return this->getInfoFromContent("/" + gidString + std::string("-") + ss.str(), 0, GETMODE_PART, std::string("href=\""), '\"');
}
