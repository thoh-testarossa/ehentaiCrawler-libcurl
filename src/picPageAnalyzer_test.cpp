//
// Created by Thoh Testarossa on 2018/1/4.
//

#include "picPageAnalyzer.h"

#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    std::string inputPage = std::string("");

    std::ifstream fin("./testPic.html", std::ios::in);
    if(fin.is_open())
    {
        while (!fin.eof())
            inputPage += fin.get();
    }
    fin.close();

    picPageAnalyzer picAna = picPageAnalyzer(inputPage);
    std::cout << picAna.getCurrentPageNumber() << std::endl;
    std::cout << picAna.getPrevPageURL() << std::endl;
    std::cout << picAna.getNextPageURL() << std::endl;
    std::cout << picAna.getLossyPicSourceURL() << std::endl;
    std::cout << picAna.getOriginalPicSourceURL() << std::endl;

    return 0;
}