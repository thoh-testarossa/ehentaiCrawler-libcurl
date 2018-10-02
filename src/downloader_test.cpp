//
// Created by Thoh Testarossa on 2018/1/2.
//

#include "downloader.h"

#include <iostream>

int main(int argc, char *argv[])
{
    std::vector<std::string> originalURLs = std::vector<std::string>();
    if (argc < 2)
    {
        originalURLs.emplace_back("https://ehgt.org/g/f.png");
        originalURLs.emplace_back("https://ehgt.org/g/p.png");
        originalURLs.emplace_back("https://ehgt.org/g/n.png");
        originalURLs.emplace_back("https://ehgt.org/g/l.png");
        originalURLs.emplace_back("https://ehgt.org/g/b.png");
    }
    else
    {
        for (int i = 1; i < argc; i++)
            originalURLs.emplace_back(argv[i]);
    }

    std::vector<std::string> patternSet = std::vector<std::string>();

    downloader dow = downloader();
    dow.curlInit(originalURLs);
    dow.findURLwithPattern(patternSet, FILTERMODE_NEW);
    dow.downloadAllURLsInSet(5, std::string("./"));

    std::map<std::string, std::string> downloadResultSet = dow.returnDownloadResultSet();

    //Write into file here
    for (auto &downloadResult : downloadResultSet)
        std::cout << downloadResult.first << " " << downloadResult.second.length() << std::endl;

    dow.curlClean();

    return 0;
}
