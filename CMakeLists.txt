cmake_minimum_required(VERSION 3.13)
project(ServerScrabble)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server Servidor/main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C json-c)
link_libraries(${JSON-C_LIBRARIES})
target_link_libraries(Server ${JSON-C_LIBRARIES})