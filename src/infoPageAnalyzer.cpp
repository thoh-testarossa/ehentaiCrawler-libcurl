#include "infoPageAnalyzer.h"

infoPageAnalyzer::infoPageAnalyzer(const string &inputPage) : pageAnalyzer(inputPage)
{
}

string infoPageAnalyzer::getComicOriginalName()
{
    return this->getInfoFromContent(string("h1 id=\"gj\""), 1, GETMODE_ALL, string(""), '\0');
}

string infoPageAnalyzer::getComicTranslatedName()
{
    return this->getInfoFromContent(string("h1 id=\"gn\""), 1, GETMODE_ALL, string(""), '\0');
}

string infoPageAnalyzer::getFirstPicPageURL()
{
    return this->getInfoFromContent(string("img alt=\""), -2, GETMODE_PART, string("href=\""), '\"');
}

int infoPageAnalyzer::getTotalPageNumber()
{
    return stoi(this->getInfoFromContent(string("Length"), 4, GETMODE_PART, string(""), ' '));
}
