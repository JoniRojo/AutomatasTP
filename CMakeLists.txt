cmake_minimum_required(VERSION 3.25)
project(tp)

set(CMAKE_CXX_STANDARD 17)


add_executable(tp automata.c automata.h Main1/main.c linkedlist.c linkedlist.h arreglo.c arreglo.h Main2/main.c)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/origin.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/aut.txt
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})