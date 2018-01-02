#include <iostream>
#include "picPageAnalyzer.h"
#include "infoPageAnalyzer.h"
#include "downloader.h"

using namespace std;

int main(int argc, char *argv[])
{
    std::cout << "Hello World!" << std::endl;
    std::vector<std::string> originalURLs = std::vector<std::string>();
    downloader dow = downloader(originalURLs);
    return 0;
}
