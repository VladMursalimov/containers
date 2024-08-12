# cmake_minimum_required(VERSION <specify CMake version here>)
project(s21_containers)

set(CMAKE_CXX_STANDARD 14)

include_directories(s21_containers)

add_executable(s21_containers
        s21_containers/list/list.cpp
        s21_containers/list/list.h
        s21_containers/queue/queue.h
        s21_containers/main.cpp
        s21_containers/stack/stack.h
        s21_containers/vector/vector.h
        s21_containers/vector/vector.cpp
        s21_containers/setMap/map/s21_map.tpp
        s21_containers/setMap/map/s21_map.h
        s21_containers/setMap/avlTree/s21_avl_tree.tpp
        s21_containers/setMap/iterators/s21_iterator.h
        s21_containers/setMap/avlTree/s21_avl_tree.h
        s21_containers/setMap/set/s21_set.h
        s21_containers/setMap/set/s21_set.tpp
)
