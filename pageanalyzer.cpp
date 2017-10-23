#include "pageAnalyzer.h"

#define INSIDE_ANGLEBRACKET 17
#define OUTSIDE_ANGLEBRACKET 18

infoPageAnalyzer::infoPageAnalyzer(const string &inputPage)
{
    this->inputPage = inputPage;
    this->decomposePageContent();
}

void infoPageAnalyzer::decomposePageContent()
{
    string tmp = string("");
    int state = OUTSIDE_ANGLEBRACKET;
    for(int i = ; i < this->inputPage.length(); i++)
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

string infoPageAnalyzer::getComicOriginalName()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("h1 id=\"gj\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
            result = this->pageContent[++pos];
    }
    return result;
}

string infoPageAnalyzer::getComicTranslatedName()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("h1 id=\"gn\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
            result = this->pageContent[++pos];
    }
    return result;
}

string infoPageAnalyzer::getFirstPicPageURL()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("img alt=\"001\"")) != string::npos ||
           this->pageContent[pos].find(string("img alt=\"01\"")) != string::npos ||
           this->pageContent[pos].find(string("img alt=\"1\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            pos -= 2;
            string prefix = string("href=\"");
            int urlpos = this->pageContent[pos].find(prefix) + prefix.length();
            if(urlpos - prefix.length() == string::npos);
            else
            {
                for(int i = urlpos; this->pageContent[pos][i] != '\"'; i++)
                    result += this->pageContent[pos][i];
            }
        }
    }
    return result;
}

int infoPageAnalyzer::getTotalPageNumber()
{
    int result = 0;
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("Length")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            pos += 4;
            string result_s = this->pageContent[pos];
            for(int i = 0; result_s[i] != ' '; i++)
                result = result * 10 + result_s[i] - '0';
        }
    }
    return result;
}

picPageAnalyzer::picPageAnalyzer(const string &inputPage)
{
    this->inputPage = inputPage;
    this->decomposePageContent();
}

void picPageAnalyzer::decomposePageContent()
{
    string tmp = string("");
    int state = OUTSIDE_ANGLEBRACKET;
    for(int i = ; i < this->inputPage.length(); i++)
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

string picPageAnalyzer::getNextPageURL()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("id=\"next\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            string prefix = string("href=\"");
            int urlpos = this->pageContent[pos].find(prefix) + prefix.length();
            if(urlpos - prefix.length() == string::npos);
            else
            {
                for(int i = urlpos; this->pageContent[pos][i] != '\"'; i++)
                    result += this->pageContent[pos][i];
            }
        }
    }
    return result;
}

string picPageAnalyzer::getPrevPageURL()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("id=\"prev\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            string prefix = string("href=\"");
            int urlpos = this->pageContent[pos].find(prefix) + prefix.length();
            if(urlpos - prefix.length() == string::npos);
            else
            {
                for(int i = urlpos; this->pageContent[pos][i] != '\"'; i++)
                    result += this->pageContent[pos][i];
            }
        }
    }
    return result;
}

int picPageAnalyzer::getCurrentPageNumber()
{
    int result = 0;
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("span")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            pos += 1;
            string result_s = this->pageContent[pos];
            result = atoi(result_s.c_str());
        }
    }
    return result;
}

string picPageAnalyzer::getLossyPicSourceURL()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("img id=\"img\"")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            string prefix = string("src=\"");
            int urlpos = this->pageContent[pos].find(prefix) + prefix.length();
            if(urlpos - prefix.length() == string::npos);
            else
            {
                for(int i = urlpos; this->pageContent[pos][i] != '\"'; i++)
                    result += this->pageContent[pos][i];
            }
        }
    }
    return result;
}

string picPageAnalyzer::getOriginalPicSourceURL()
{
    string result = string("");
    int pos = 0;
    for(; pos < this->pageContent.size(); pos++)
    {
        if(this->pageContent[pos].find(string("Download original")) != string::npos) break;
        if(pos == pageContent.size());
        else
        {
            pos -= 1;
            string prefix = string("href=\"");
            int urlpos = this->pageContent[pos].find(prefix) + prefix.length();
            if(urlpos - prefix.length() == string::npos);
            else
            {
                for(int i = urlpos; this->pageContent[pos][i] != '\"'; i++)
                {
                    result += this->pageContent[pos][i];
                    //To change the html "&amp; form to "&" for the correct link
                    //It means to jump the "amp;" part
                    if(this->pageContent[pos][i] == '&') i += 4;
                }
            }
        }
    }
    return result;
}
