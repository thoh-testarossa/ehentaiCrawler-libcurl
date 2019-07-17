cmake_minimum_required(VERSION 3.9)
project(ehentaiCrawler-libcurl)

set(CMAKE_CXX_STANDARD 14)

add_executable(infoPageAnalyzer_test
        infoPageAnalyzer_test.cpp)

target_link_libraries(infoPageAnalyzer_test
        infoPageAnalyzer)

add_executable(picPageAnalyzer_test
        picPageAnalyzer_test.cpp)

target_link_libraries(picPageAnalyzer_test
        picPageAnalyzer)