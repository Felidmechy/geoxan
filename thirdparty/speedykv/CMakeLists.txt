cmake_minimum_required(VERSION 3.5)

project(speedykv LANGUAGES CXX)

add_library(speedykv STATIC ${CMAKE_CURRENT_LIST_DIR}/src/KeyValue.cpp)

