cmake_minimum_required(VERSION 3.0)

project("BookShop")

add_executable("BookSystem" MainMenu.cpp BookSystemStruct.cpp BookSystemStruct.h)

include_directories(${PROJECT_SOURCE_DIR} "json/include/")

set(CMAKE_CXX_FLAGS "-std=c++11 -O3")