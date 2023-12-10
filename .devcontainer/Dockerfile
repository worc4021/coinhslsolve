# syntax=docker/dockerfile-upstream:master-labs
FROM worc4021/hsl

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install git \
            build-essential \
            cmake \
            ninja-build \
            clang-format \
            sudo \
            gcc \
            g++ \
            gfortran \
            lsb-release \
            gdb \
            python3 \
            python3-pybind11 \
            pip \
            pkg-config \
            libblas-dev \
            liblapack-dev \
            curl \
            zip \
            unzip \
            tar \
            autoconf \
            valgrind
            
ARG USERNAME

RUN adduser --disabled-password --gecos '' ${USERNAME} && \
    adduser ${USERNAME} sudo && \
    echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
