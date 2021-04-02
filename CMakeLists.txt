cmake_minimum_required(VERSION 3.17)
project(Graph C)

set(CMAKE_C_STANDARD 11)

add_executable(Graph main.c Container.h Container.c Private.h Private.c LinkedList.h LinkedList.c LinkedListTest.h LinkedListTest.c)