cmake_minimum_required(VERSION 3.13)
project(Scrabble)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Scrabble
        README.md Ficha.cpp Ficha.h FichaCreator.cpp FichaCreator.h Juego.cpp Juego.h Jugador.cpp
        Jugador.h List.cpp List.h mainCLion.cpp NodeFicha.cpp NodeFicha.h Cuadricula.cpp Cuadricula.h)


find_package(PkgConfig REQUIRED)
pkg_check_modules(JSON-C json-c)
link_libraries(${JSON-C_LIBRARIES})
target_link_libraries(Scrabble ${JSON-C_LIBRARIES})
