#include "picPageAnalyzer.h"

picPageAnalyzer::picPageAnalyzer(const string &inputPage) : pageAnalyzer(inputPage)
{
}

string picPageAnalyzer::getNextPageURL()
{
    return this->getInfoFromContent(string("id=\"next\""), 0, GETMODE_PART, string("href=\""), '\"');
}

string picPageAnalyzer::getPrevPageURL()
{
    return this->getInfoFromContent(string("id=\"prev\""), 0, GETMODE_PART, string("href=\""), '\"');
}

int picPageAnalyzer::getCurrentPageNumber()
{
    return stoi(this->getInfoFromContent(string("span"), 1, GETMODE_ALL, string(""), '\0'));
}

string picPageAnalyzer::getLossyPicSourceURL()
{
    return this->getInfoFromContent(string("img id=\"img\""), 0, GETMODE_PART, string("src=\""), '\"');
}

string picPageAnalyzer::getOriginalPicSourceURL()
{
    string result_middle = this->getInfoFromContent(string("Download original"), -1, GETMODE_PART, string("href=\""), '\"');
    string result = string("");

    //Part to handle special character "&amp;". It will be replaced by a more uniform function in the future
    while(int errpos = result_middle.find(string("&amp;")) != string::npos)
    {
        int rpos = 0;
        for(rpos = 0; rpos < errpos; rpos++)
            result += result_middle[rpos];

        result += result[errpos];

        for(; rpos < result_middle.length() - (string("&amp;").length() - 1); rpos++)
            result += result_middle[rpos + string("&amp;").length() - 1];
    }
    return result;
}
