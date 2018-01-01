#ifndef CONFIG_H
#define CONFIG_H

#include "config.h"

#endif

#ifndef P_ANALYZER_H
#define P_ANALYZER_H

#include "pageAnalyzer.h"

#endif

#ifndef PICPAGEANALYZER_H
#define PICPAGEANALYZER_H

class picPageAnalyzer : public pageAnalyzer
{
public:
    picPageAnalyzer(const string &inputPage);
    string getNextPageURL();
    string getPrevPageURL();
    string getLossyPicSourceURL();
    string getOriginalPicSourceURL();
    int getCurrentPageNumber();
};

#endif // PICPAGEANALYZER_H
