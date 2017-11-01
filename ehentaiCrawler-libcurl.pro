TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    pageAnalyzer.cpp \
    infoPageAnalyzer.cpp \
    picPageAnalyzer.cpp \
    downloader.cpp

HEADERS += \
    pageAnalyzer.h \
    commonHeader.h \
    infoPageAnalyzer.h \
    picPageAnalyzer.h \
    downloader.h
