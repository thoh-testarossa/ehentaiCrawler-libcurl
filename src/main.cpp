#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include "picPageAnalyzer.h"
#include "infoPageAnalyzer.h"
#include "downloader.h"

using namespace std;

//The template usage for the classes in this project
int main(int argc, char *argv[])
{
    //Initialize the program
    downloader dow = downloader();
    std::vector<std::string> originURLs = std::vector<std::string>();
    std::vector<std::string> patternSet = std::vector<std::string>();
    std::map<std::string, std::string> downloadResultSet = std::map<std::string, std::string>();

    std::string path = std::string("./");

    //Analyse the parameters in the argv[]
    //Note: this part will be filled by using a parser class which will be added into this project in future
    std::vector<std::string> parameterSet = std::vector<std::string>();
    for(int i = 1; i < argc; i++) parameterSet.emplace_back(argv[i]);

    std::string infoPageURL = (argc >= 2) ?
                              std::string(argv[1]) :
                              std::string("https://e-hentai.org/g/1164260/d72b2fcc89/");

    //Used for changing int to string
    std::stringstream ss = std::stringstream();

    //Get the information page
    std::vector<std::string> infoPages = std::vector<std::string>();

    originURLs.clear();
    patternSet.clear();
    downloadResultSet.clear();

    originURLs.push_back(infoPageURL);
    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResultSet = dow.returnDownloadResultSet();

    dow.curlClean();

    //Analyse the information page
    std::string infoPage = std::string("");
    for (auto &downloadResult : downloadResultSet) infoPage = downloadResult.second;

    infoPages.push_back(infoPage);

    infoPageAnalyzer infoAna = infoPageAnalyzer(infoPage);

    int pageCount = infoAna.getTotalPageNumber();
    std::string comicOName = infoAna.getComicOriginalName();
    std::string comicTName = infoAna.getComicTranslatedName();
    std::string gidString = infoAna.getGidInString();

    //Get other info pages
    originURLs.clear();
    patternSet.clear();
    downloadResultSet.clear();

    for (int i = 1; i < ceil((double) pageCount / picPagesPerInfoPage); i++)
    {
        ss.str("");

        std::string suffix = std::string("");
        if (infoPageURL[infoPageURL.length() - 1] != '/') suffix += '/';
        suffix += std::string("?p=");

        ss << i;
        suffix += ss.str();

        originURLs.push_back(infoPageURL + suffix);
    }

    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResultSet = dow.returnDownloadResultSet();

    dow.curlClean();

    for (auto &downloadResult : downloadResultSet) infoPages.push_back(downloadResult.second);

    //Get all the pic page URLs from these info pages
    std::vector<std::string> picPageURLs = std::vector<std::string>();
    std::vector<infoPageAnalyzer> infoAnaContainer = std::vector<infoPageAnalyzer>();
    infoAnaContainer.push_back(infoAna);
    for (int i = 1; i < infoPages.size(); i++) infoAnaContainer.emplace_back(infoPages[i]);
    for (int i = 1; i <= pageCount; i++)
    {
        std::string picPageURL = std::string("");
        for (auto &infoAnaForPage : infoAnaContainer)
        {
            picPageURL = infoAnaForPage.getPicPageURL(gidString, i);
            if (picPageURL != std::string("")) break;
        }
        picPageURLs.push_back(picPageURL);
    }

    //Get all the pic pages
    std::vector<std::string> picPages = std::vector<std::string>();

    originURLs.clear();
    patternSet.clear();
    downloadResultSet.clear();

    originURLs = picPageURLs;
    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResultSet = dow.returnDownloadResultSet();

    dow.curlClean();

    for (auto &downloadResult : downloadResultSet) picPages.push_back(downloadResult.second);

    //Get all the download URLs of pics from the pic page
    std::vector<std::string> picURLs = std::vector<std::string>();
    for (auto &picPage : picPages) picURLs.push_back(picPageAnalyzer(picPage).getLossyPicSourceURL());

    //Download all the pics concurrently
    originURLs.clear();
    patternSet.clear();
    downloadResultSet.clear();

    originURLs = picURLs;
    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResultSet = dow.returnDownloadResultSet();

    //Write them back to the file
    for (auto &downloadResult : downloadResultSet)
    {
        std::ofstream fout(downloadResult.first, std::ios::out | std::ios::binary);
        if (fout.is_open()) fout.write(downloadResult.second.c_str(), downloadResult.second.length());
        fout.close();
    }

    return 0;
}
