#include "pageAnalyzer.h"

#define OUTSIDE_ANGLEBRACKET 23
#define INSIDE_ANGLEBRACKET 24

pageAnalyzer::pageAnalyzer(const string &inputPage)
{
    this->inputPage = inputPage;
    this->decomposePageContent();
}

void pageAnalyzer::decomposePageContent()
{
    string tmp = string("");
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

string pageAnalyzer::getInfoFromContent(const string &keyToFindTarStr, int offset, int getMode, const string &keyToFindPos, char endChar)
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
        if(this->pageContent[pos].find(keyToFindTarStr) != string::npos) break;
    if(pos == pageContent.size());
    else
    {
        pos += offset;
        if(getMode == GETMODE_ALL) result = this->pageContent[pos];
        else if(getMode == GETMODE_PART)
        {
            int startPos = this->pageContent[pos].find(keyToFindPos) + keyToFindPos.length();
            if(startPos - keyToFindPos.length() == string::npos);
            else
                for(int i = startPos; this->pageContent[pos][i] != endChar; i++)
                    result += this->pageContent[pos][i];
        }
    }
    return result;
}
