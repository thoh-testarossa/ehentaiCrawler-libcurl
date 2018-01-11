# ehentaiCrawler-libcurl

ehentaiCrawler-libcurl is a C++-written crawler which can download comics from e-hentai/exhentai easily

## System Requirement

A suitable C++11 compiler is necessary (such as clang, g++-5 and so on)

Also, you still need a cmake with version newer than 3.9 to compile it easily, but it's no matter whether you use cmake or not.

## Config
Sometimes you may be interested in changing some configurations of this program to make a different experience. Some of them are listed in config.h.

## Installation

Clone this project to your local machine and move to the root directory of this project

```
cd [path]/[to]/adb-BufferSystem
```

Create a build directory

```
mkdir build
cd build
```

Execute cmake

```
cmake ..
```

Compile this project

```
make
```

After that, you will see 4 executables in the ./bin directory: one for use and other three for test.

## Usage

The executable named ehentaiCrawler_libcurl is the one we need. 

To use it, you should give this executable a parameter: the information page's URL of the comic you want to download on ehentai or exhentai. Otherwise it will start downloading from a default URL on ehentai

The program will finish all the other things and finally you will find your comic downloaded and placed in somewhere in ./bin

The executables named xxx-test is the test part for the classes written by me^_^. It's not necessary to run them for any kind of prepare works. But, you should put some test files shown in the code into ./bin directory if you insist executing them.

## Parts finished

Page content analyzer

Multi-thread Downloader using libcurl

## Todo List

Support for cookies

Timeout control