# cmake_minimum_required(VERSION <specify CMake version here>)
project(s21_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(s21_containers)

add_executable(s21_containers
        s21_containers/list.cpp
        s21_containers/list.h
        s21_containers/main.cpp)
