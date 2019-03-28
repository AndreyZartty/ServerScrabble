cmake_minimum_required(VERSION 3.13)
project(ServerScrabble)

set(CMAKE_CXX_STANDARD 14)

add_executable(server.cpp Servidor/main.cpp)