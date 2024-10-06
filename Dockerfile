FROM ubuntu:22.04

RUN apt-get update -y \
  && apt-get install -y wget g++ make xz-utils m4 cmake doxygen libopenblas-dev \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/*

WORKDIR /home/manifold-opt/
