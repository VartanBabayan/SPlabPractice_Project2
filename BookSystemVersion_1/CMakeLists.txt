cmake_minimum_required(VERSION 3.0)

project(BookShop)

include_directories(${PROJECT_SOURCE_DIR}/json/include/)

set(SOURCE_EXE MainMenu.cpp BookSystemStruct.cpp)

#set(SOURCE_LIB BookSystemStruct.cpp)

add_executable(MainMenu ${SOURCE_EXE})
