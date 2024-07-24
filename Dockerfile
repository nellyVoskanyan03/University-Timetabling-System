FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    libgtest-dev \
    cmake \
    wget \
    unzip \
    git \
    dos2unix \
    make


WORKDIR /usr/src/app

COPY . /usr/src/app

RUN dos2unix /usr/src/app/run.sh

RUN chmod +x /usr/src/app/run.sh

RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make


CMD ["/usr/src/app/run.sh"]