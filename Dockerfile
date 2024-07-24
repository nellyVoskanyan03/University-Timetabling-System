FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    libgtest-dev \
    cmake \
    wget \
    unzip \
    git \
    make


RUN mkdir -p /usr/src/app/
WORKDIR /usr/src/app/

COPY . .

WORKDIR /usr/src/app/script/
RUN chmod +x b.sh
CMD ["sh","./build.sh"]