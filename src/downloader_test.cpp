//
// Created by Thoh Testarossa on 2018/1/2.
//

#include "downloader.h"

int main(int argc, char *argv[])
{
    std::vector<std::string> originalURLs = std::vector<std::string>();
    if(argc < 2)
        originalURLs.push_back(std::string("https://ehgt.org/g/f.png"));
    else
    {
        for(int i = 1; i < argc; i++)
            originalURLs.push_back(std::string(argv[i]));
    }

    std::vector<std::string> patternSet = std::vector<std::string>();

    downloader dow = downloader(originalURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(1, std::string("./"));

    std::map<std::string, std::string> downloadResult = dow.returnDownloadResultSet();

    //Write into file here

    dow.~downloader();

    return 0;
}