#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"

#endif

#ifndef P_ANALYZER_H
#define P_ANALYZER_H

#include "pageAnalyzer.h"

#endif

#ifndef INFOPAGEANALYZER_H
#define INFOPAGEANALYZER_H

class infoPageAnalyzer : public pageAnalyzer
{
public:
    infoPageAnalyzer(const string &inputPage);
    string getComicOriginalName();
    string getComicTranslatedName();
    string getFirstPicPageURL();
    int getTotalPageNumber();
};

#endif // INFOPAGEANALYZER_H
