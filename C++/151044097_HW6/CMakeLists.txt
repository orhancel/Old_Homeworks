cmake_minimum_required(VERSION 3.7)
project(HW6)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp GTUSetBase.h GTUSet.h GTUSet.cpp GTUMap.h GTUIterator.h GTUMap.cpp GTUIterator.cpp)
add_executable(HW6 ${SOURCE_FILES})