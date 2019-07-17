cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler-libcurl)

set(CMAKE_CXX_STANDARD 14)

add_library(pageAnalyzer
        pageAnalyzer.h
        pageAnalyzer.cpp)

add_library(picPageAnalyzer
        picPageAnalyzer.h
        picPageAnalyzer.cpp)

target_link_libraries(picPageAnalyzer
        pageAnalyzer)

add_library(infoPageAnalyzer
        infoPageAnalyzer.h
        infoPageAnalyzer.cpp)

target_link_libraries(infoPageAnalyzer
        pageAnalyzer)

