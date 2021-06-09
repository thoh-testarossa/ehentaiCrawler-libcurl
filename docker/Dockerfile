# Author: Thoh Testarossa by 2021-06-09
FROM ubuntu
MAINTAINER Thoh Testarossa "thoh.testarossa@gmail.com"
ENV REFRESHED_AT 2021-06-09
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get install -y git g++ cmake libcurl4-openssl-dev

RUN git clone https://github.com/thoh-testarossa/ehentaiCrawler-libcurl.git
RUN cd ehentaiCrawler-libcurl && git submodule update --init
RUN mkdir ehentaiCrawler-libcurl/build
RUN cd ehentaiCrawler-libcurl/build && cmake .. && make
RUN ln -s ehentaiCrawler-libcurl/build/bin/ehentaiCrawler-libcurl ./ehentaiCrawler-libcurl

EXPOSE 443 80 22
CMD ["/bin/bash", "-D"]

