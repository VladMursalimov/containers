# cmake_minimum_required(VERSION <specify CMake version here>)
project(s21_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(s21_containers)

add_executable(s21_containers
        s21_containers/list/list.cpp
        s21_containers/list/list.h
        s21_containers/tests.cpp
        s21_containers/vector/vector.cpp
s21_containers/stack/stack.h
s21_containers/queue/queue.h)
