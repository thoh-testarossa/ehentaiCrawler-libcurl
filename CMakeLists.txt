cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler-libcurl)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_subdirectory(src/downloader-libcurl)
add_subdirectory(src/pageAnalyzer)

add_subdirectory(src/test)

add_executable(ehentaiCrawler-libcurl
        src/ehentaiCrawler-libcurl.cpp)

target_link_libraries(ehentaiCrawler-libcurl
        downloader
        pageAnalyzer
        infoPageAnalyzer
        picPageAnalyzer)
