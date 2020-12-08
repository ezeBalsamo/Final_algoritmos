cmake_minimum_required(VERSION 3.16)
project(FinalAyed_VonWeber C)

set(CMAKE_C_STANDARD 99)

add_executable(FinalAyed_VonWeber main.c algoritmo_de_cifrado.c algoritmo_de_cifrado.h strings_lib.c strings_lib.h)
target_link_libraries(FinalAyed_VonWeber)