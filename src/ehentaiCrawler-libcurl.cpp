#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cmath>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "pageAnalyzer/picPageAnalyzer.h"
#include "pageAnalyzer/infoPageAnalyzer.h"
#include "downloader-libcurl/downloader/downloader-libcurl.h"

using namespace std;

//The template usage for the classes in this project
int main(int argc, char *argv[])
{
    //Initialize the program
    Downloader_libcurl dow = Downloader_libcurl();
    auto originURLs = std::vector<std::string>();
    auto patternSet = std::vector<std::string>();
    auto downloadResultSet = std::vector<std::pair<std::string, std::string>>();

    std::string path = std::string("./");

    //Analyse the parameters in the argv[]
    //Note: this part will be filled by using a parser class which will be added into this project in future
    auto parameterSet = std::vector<std::string>();
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
    dow.downloadedFileSet.clear();
    downloadResultSet.clear();

    originURLs.push_back(infoPageURL);
    //dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadURLSet = originURLs;
    dow.downloadAll(threadNum, path, false);
    downloadResultSet = dow.downloadedFileSet;

    //dow.curlClean();

    //Analyse the information page
    std::string infoPage = std::string("");
    for (auto &downloadResult : downloadResultSet) infoPage = downloadResult.second;

    infoPages.push_back(infoPage);

    infoPageAnalyzer infoAna = infoPageAnalyzer(infoPage);

    int pageCount = infoAna.getTotalPageNumber();
    std::string comicOName = infoAna.getComicOriginalName();
    std::string comicTName = infoAna.getComicTranslatedName();
    std::string gidString = infoAna.getGidInString();

    //Build comic directory
    if(access(comicOName.c_str(), F_OK) == -1)
        mkdir(comicOName.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);

    path += comicOName + std::string("/");
    //Test
    std::cout << path << std::endl;

    //Get other info pages
    originURLs.clear();
    patternSet.clear();
    dow.downloadedFileSet.clear();
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

    dow.downloadURLSet = originURLs;
    dow.downloadAll(threadNum, path, false);
    downloadResultSet = dow.downloadedFileSet;

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
    dow.downloadedFileSet.clear();
    downloadResultSet.clear();

    originURLs = picPageURLs;
    dow.downloadURLSet = originURLs;
    //dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAll(threadNum, path, false);
    downloadResultSet = dow.downloadedFileSet;

    //Get all the download URLs of pics from the pic page
    std::vector<std::string> picURLs = std::vector<std::string>();

    for(const auto &downloadResult : downloadResultSet)
    {
        auto picURL = picPageAnalyzer(downloadResult.second).getLossyPicSourceURL();
        picURLs.push_back(picURL);
        //Test
        std::cout << downloadResult.first << " -> " << picURL << endl;
    }

    //Download all the pics concurrently
    originURLs.clear();
    patternSet.clear();
    dow.downloadedFileSet.clear();
    downloadResultSet.clear();

    originURLs = picURLs;
    dow.downloadURLSet= originURLs;
    //dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAll(threadNum, path, true);

    /*
    downloadResultSet = dow.returnDownloadResultSet();

    //Write them back to the file
    for (auto &downloadResult : downloadResultSet)
    {
        std::ofstream fout(downloadResult.first, std::ios::out | std::ios::binary);
        if (fout.is_open()) fout.write(downloadResult.second.c_str(), downloadResult.second.length());
        fout.close();
    }
     */

    return 0;
}
