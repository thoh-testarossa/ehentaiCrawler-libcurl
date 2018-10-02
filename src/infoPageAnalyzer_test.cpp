//
// Created by Thoh Testarossa on 2018/1/4.
//

#include "infoPageAnalyzer.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string inputPage = std::string("");

    std::ifstream fin("./testInfo.html", std::ios::in);
    if(fin.is_open())
    {
        while (!fin.eof())
            inputPage += (char)fin.get();
    }
    fin.close();

    infoPageAnalyzer infoAna = infoPageAnalyzer(inputPage);
    std::cout << infoAna.getComicOriginalName() << std::endl;
    std::cout << infoAna.getComicTranslatedName() << std::endl;
    std::cout << infoAna.getFirstPicPageURL() << std::endl;
    std::cout << infoAna.getTotalPageNumber() << std::endl;

    return 0;
}