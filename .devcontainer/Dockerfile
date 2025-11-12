FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

# Set the timezone environment variable
ENV TZ=Asia/Hong_Kong
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# For ubuntu:24.04, there already have a user named `ubuntu` with uid 1000, we need to delete it. see:
# https://askubuntu.com/questions/1513927/ubuntu-24-04-docker-images-now-includes-user-ubuntu-with-uid-gid-1000
RUN touch /var/mail/ubuntu && chown ubuntu /var/mail/ubuntu && userdel -r ubuntu

# Set apt mirror
RUN rm /etc/apt/sources.list.d/ubuntu.sources
COPY hk.ubuntu.sources /etc/apt/sources.list.d/hk.ubuntu.sources

# Install packages
RUN apt-get clean && \
    apt-get update -y && \
    apt-get install -y --no-install-recommends apt-utils && \
    apt-get install -y \
    # Basic utilities
    tzdata tar unzip zip iproute2 git vim nano curl sudo procps \
    # GCC 14
    gcc-14 g++-14  \
    # Clang 17
    clang-17 clang++-17 lldb-17 libc++-17-dev libc++abi-17-dev \
    # formatters
    shfmt cmake-format \
    # Build tools
    build-essential gdb valgrind cmake ninja-build ccache \
    # Python and package manager
    python3 python3-pip python3-venv python3-full \
    pkg-config autoconf automake libtool \
    && apt-get autoremove -y \
    && apt-get clean -y

# Set the default compiler
RUN update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-14 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-14 100 \
    && update-alternatives --install /usr/bin/clang clang /usr/bin/clang-17 100 \
    && update-alternatives --install /usr/bin/clang++ clang++ /usr/bin/clang++-17 100

# Install Conan in venv
RUN python3 -m venv /opt/conan-venv \
  && /opt/conan-venv/bin/pip install --no-cache-dir --upgrade pip \
  && /opt/conan-venv/bin/pip install --no-cache-dir conan \
  && ln -s /opt/conan-venv/bin/conan /usr/local/bin/conan

# This Dockerfile adds a non-root user `developer` with sudo privileges. However, on Linux,
# this user's GID/UID must match your local user's UID/GID to avoid permission issues during bind mounts.
# If your UID/GID is not 1000, please update USER_UID / USER_GID. For more details,
# refer to https://aka.ms/vscode-remote/containers/non-root-user.
ARG USER_UID=1000
ARG USER_GID=1000
ARG USER_NAME=developer
RUN groupadd --gid $USER_GID $USER_NAME \
    && useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -m $USER_NAME \
    && echo $USER_NAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USER_NAME \
    && chmod 0440 /etc/sudoers.d/$USER_NAME

USER $USER_NAME
WORKDIR /home/$USER_NAME

# Initialize conan
RUN conan profile detect --force \
  && mkdir -p ~/.conan2/profiles \
  # Generate conan profile for gcc14
  && conan profile detect --name gcc14 --force \
  && sed -i 's|compiler.version=.*|compiler.version=14|g' ~/.conan2/profiles/gcc14 \
  && sed -i 's|compiler.cppstd=.*|compiler.cppstd=20|g' ~/.conan2/profiles/gcc14 \
  # Generate conan profile for clang17
  && conan profile detect --name clang17 --force \
  && sed -i 's|compiler=gcc|compiler=clang|g' ~/.conan2/profiles/clang17 \
  && sed -i 's|compiler.version=.*|compiler.version=17|g' ~/.conan2/profiles/clang17 \
  && sed -i 's|compiler.cppstd=.*|compiler.cppstd=20|g' ~/.conan2/profiles/clang17 \
  && sed -i 's|compiler.libcxx=.*|compiler.libcxx=libc++|g' ~/.conan2/profiles/clang17

COPY Dockerfile /tmp/Dockerfile

ENV DEBIAN_FRONTEND=dialog
