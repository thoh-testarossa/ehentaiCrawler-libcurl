cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler_libcurl)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/main.cpp
        src/config.h
        src/downloader.cpp
        src/downloader.h
        src/infoPageAnalyzer.cpp
        src/infoPageAnalyzer.h
        src/pageAnalyzer.cpp
        src/pageAnalyzer.h
        src/picPageAnalyzer.cpp
        src/picPageAnalyzer.h)

add_executable(ehentaiCrawler_libcurl ${SOURCE_FILES})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})
target_link_libraries(ehentaiCrawler_libcurl ${CURL_LIBRARIES})