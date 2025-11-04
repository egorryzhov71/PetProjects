FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

# Установка дополнительных инструментов
RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    cmake \
    cmake-curses-gui \
    gdb \
    git \
    build-essential \
    pkg-config \
    valgrind \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Создание пользователя vscode (обычно уже есть в базовом образе)
RUN useradd -m -s /bin/bash vscode && \
    usermod -aG sudo vscode

WORKDIR /workspaces