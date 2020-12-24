cmake_minimum_required(VERSION 3.17)
project(set_tree)

set(CMAKE_CXX_STANDARD 11)

add_executable(set_tree main.cpp include/set.h include/node.h include/tree.h)