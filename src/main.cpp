#include <iostream>
#include "picPageAnalyzer.h"
#include "infoPageAnalyzer.h"
#include "downloader.h"

using namespace std;

//The template usage for the classes in this project
int main(int argc, char *argv[])
{
    //Analyse the parameters in the argv[]
    //Note: this part will be filled by using a parser class which will be added into this project in future

    //Initialize the program
    downloader dow = downloader();
    std::vector<std::string> originURLs = std::vector<std::string>();
    std::vector<std::string> patternSet = std::vector<std::string>();
    std::map<std::string, std::string> downloadResult = std::map<std::string, std::string>();
    int threadNum = 5;

    std::string path = std::string("./");

    //Get the information page
    originURLs.clear();
    patternSet.clear();
    downloadResult.clear();

    std::string infoPageURL = (argc >= 2) ?
                              std::string(argv[1]) :
                              std::string("https://e-hentai.org/g/1164260/d72b2fcc89/");
    originURLs.push_back(infoPageURL);
    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResult = dow.returnDownloadResultSet();

    dow.curlClean();

    //Analyse the information page and get the first pic page
    std::string infoPage = std::string("");
    for(std::map<std::string, std::string>::iterator iter = downloadResult.begin(); iter != downloadResult.end(); iter++)
        infoPage = iter->second;

    infoPageAnalyzer infoAna = infoPageAnalyzer(infoPage);

    int pageCount = infoAna.getTotalPageNumber();
    std::string comicOName = infoAna.getComicOriginalName();
    std::string comicTName = infoAna.getComicTranslatedName();
    std::string picPageURL = infoAna.getFirstPicPageURL();

    //Get all the download URLs of pics from the 1st pic page
    std::vector<std::string> picURLs = std::vector<std::string>();
    std::string picPage = std::string("");

    for(int i = 0; i < pageCount; i++)
    {
        originURLs.clear();
        patternSet.clear();
        downloadResult.clear();

        originURLs.push_back(picPageURL);
        dow.curlInit(originURLs);
        dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
        dow.downloadAllURLsInSet(threadNum, path);
        downloadResult = dow.returnDownloadResultSet();

        dow.curlClean();

        for(std::map<std::string, std::string>::iterator iter = downloadResult.begin(); iter != downloadResult.end(); iter++)
        {
            picPage = iter->second;
            picURLs.push_back(picPage);

            picPageAnalyzer picAna = picPageAnalyzer(picPage);

            picPageURL = picAna.getNextPageURL();
            picURLs.push_back(picAna.getLossyPicSourceURL());
        }
    }

    //Download all the pics concurrently
    originURLs.clear();
    patternSet.clear();
    downloadResult.clear();

    originURLs = picURLs;
    dow.curlInit(originURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(threadNum, path);
    downloadResult = dow.returnDownloadResultSet();

    //Write them back to the file
    //Need to be added

    return 0;
}
