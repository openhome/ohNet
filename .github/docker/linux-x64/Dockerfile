FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    gcc-9 \
    g++-9 \
    ca-certificates \
    curl \
    libicu70 \
    python3 \
    python3-pip \
    python-is-python3 \
    mono-devel \
    rsync \
    && rm -rf /var/lib/apt/lists/*

RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 90
RUN update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 90
RUN pip3 install --no-cache-dir requests
