cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler_libcurl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/commonHeader.h
        src/downloader.cpp
        src/downloader.h
        src/infoPageAnalyzer.cpp
        src/infoPageAnalyzer.h
        src/main.cpp
        src/pageAnalyzer.cpp
        src/pageAnalyzer.h
        src/picPageAnalyzer.cpp
        src/picPageAnalyzer.h)

add_executable(ehentaiCrawler_libcurl ${SOURCE_FILES})