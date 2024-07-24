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


# Set the working directory
WORKDIR /usr/s/app

# Copy the current directory contents into the container at /usr/s/app
COPY . /usr/s/app

# Create a build directory and run cmake, make
RUN mkdir -p build && \
    cd build && \
    cmake .. && \
    make

# Command to run your application
CMD ["./build/UniversityTimetablingSystem"]