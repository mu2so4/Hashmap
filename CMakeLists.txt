cmake_minimum_required(VERSION 3.20)
project(my_hashmap)

find_package(Catch2 3 REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_hashmap main.cpp MyHashMap.h MyHashMap.cpp list.cpp item.cpp iterator.cpp)
