cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler-libcurl)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

set(SOURCE_FILES
        src/infoPageAnalyzer_test.cpp
        src/config.h
        src/pageAnalyzer.h
        src/pageAnalyzer.cpp
        src/infoPageAnalyzer.h
        src/infoPageAnalyzer.cpp)

add_executable(infoPageAnalyzer_test ${SOURCE_FILES})

set(SOURCE_FILES
        src/picPageAnalyzer_test.cpp
        src/config.h
        src/pageAnalyzer.h
        src/pageAnalyzer.cpp
        src/picPageAnalyzer.h
        src/picPageAnalyzer.cpp)

add_executable(picPageAnalyzer_test ${SOURCE_FILES})

set(SOURCE_FILES
        src/downloader_test.cpp
        src/config.h
        src/downloader.h
        src/downloader.cpp)

add_executable(downloader_test ${SOURCE_FILES})

target_link_libraries(downloader_test ${CURL_LIBRARIES})

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

target_link_libraries(ehentaiCrawler_libcurl ${CURL_LIBRARIES})
