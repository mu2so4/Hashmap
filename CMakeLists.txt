cmake_minimum_required(VERSION 3.20)
project(my_hashmap)

find_package(Catch2 3 REQUIRED)


add_executable(basic-test tests/basic_functions_test.cpp)
target_link_libraries(basic-test PRIVATE Catch2::Catch2WithMain)

add_executable(at-test tests/at_test.cpp)
target_link_libraries(at-test PRIVATE Catch2::Catch2WithMain)

add_executable(copy-move-test tests/copy_move_test.cpp)
target_link_libraries(copy-move-test PRIVATE Catch2::Catch2WithMain)

add_executable(special-test tests/special_functions_test.cpp)
target_link_libraries(special-test PRIVATE Catch2::Catch2WithMain)

add_executable(iterator-test tests/iterator_test.cpp)
target_link_libraries(iterator-test PRIVATE Catch2::Catch2WithMain)

set(CMAKE_CXX_STANDARD 17)

add_executable(my_hashmap main.cpp MyHashMap.h)


