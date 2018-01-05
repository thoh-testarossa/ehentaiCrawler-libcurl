#include "picPageAnalyzer.h"

picPageAnalyzer::picPageAnalyzer(const std::string &inputPage) : pageAnalyzer(inputPage)
{
}

std::string picPageAnalyzer::getNextPageURL()
{
    return this->getInfoFromContent(std::string("id=\"next\""), 0, GETMODE_PART, std::string("href=\""), '\"');
}

std::string picPageAnalyzer::getPrevPageURL()
{
    return this->getInfoFromContent(std::string("id=\"prev\""), 0, GETMODE_PART, std::string("href=\""), '\"');
}

int picPageAnalyzer::getCurrentPageNumber()
{
    return stoi(this->getInfoFromContent(std::string("span"), 1, GETMODE_ALL, std::string(""), '\0'));
}

std::string picPageAnalyzer::getLossyPicSourceURL()
{
    return this->getInfoFromContent(std::string("img id=\"img\""), 0, GETMODE_PART, std::string("src=\""), '\"');
}

std::string picPageAnalyzer::getOriginalPicSourceURL()
{
    std::string result_middle = this->getInfoFromContent(std::string("Download original"), -1, GETMODE_PART, std::string("href=\""), '\"');
    std::string result = std::string("");

    //Part to handle special character "&amp;". It will be replaced by a more uniform function in the future
    int errpos = result_middle.find(std::string("&amp;"));
    while(errpos != std::string::npos)
    {
        result.clear();
        int rpos = 0;
        for(rpos = 0; rpos < errpos; rpos++)
            result += result_middle[rpos];

        result += result_middle[errpos];

        rpos += std::string("&amp;").length();

        for(; rpos < result_middle.length(); rpos++)
            result += result_middle[rpos];

        result_middle = result;

        errpos = result_middle.find(std::string("&amp;"));
    }
    return result;
}
