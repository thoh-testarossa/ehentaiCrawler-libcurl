#include "pageAnalyzer.h"

#define OUTSIDE_ANGLEBRACKET 23
#define INSIDE_ANGLEBRACKET 24

pageAnalyzer::pageAnalyzer(const std::string &inputPage)
{
    this->inputPage = inputPage;
    this->decomposePageContent();
}

void pageAnalyzer::decomposePageContent()
{
    std::string tmp = std::string("");
    int state = OUTSIDE_ANGLEBRACKET;
    for(int i = 0; i < this->inputPage.length(); i++)
    {
        if(state == OUTSIDE_ANGLEBRACKET)
        {
            if(this->inputPage[i] != '<')
                tmp += this->inputPage[i];
            else
            {
                state = INSIDE_ANGLEBRACKET;
                this->pageContent.push_back(tmp);
                tmp.clear();
            }
        }
        else if(state == INSIDE_ANGLEBRACKET)
        {
            if(this->inputPage[i] != '>')
                tmp += this->inputPage[i];
            else
            {
                state = OUTSIDE_ANGLEBRACKET;
                this->pageContent.push_back(tmp);
                tmp.clear();
            }
        }
    }
}

std::string pageAnalyzer::getInfoFromContent(const std::string &keyToFindTarStr, int offset, int getMode, const std::string &keyToFindPos, char endChar)
{
    std::string result = std::string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
        if(this->pageContent[pos].find(keyToFindTarStr) != std::string::npos) break;
    if(pos == pageContent.size());
    else
    {
        pos += offset;
        if(getMode == GETMODE_ALL) result = this->pageContent[pos];
        else if(getMode == GETMODE_PART)
        {
            int startPos = this->pageContent[pos].find(keyToFindPos) + keyToFindPos.length();
            if(startPos - keyToFindPos.length() == std::string::npos);
            else
                for(int i = startPos; this->pageContent[pos][i] != endChar; i++)
                    result += this->pageContent[pos][i];
        }
    }
    return result;
}
