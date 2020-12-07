cmake_minimum_required(VERSION 3.0)

project("BookShop")

set(CMALE_CXX_FLAGS "-std=c++11 -03")

include_directories(${PROJECT_SOURCE_DIR})

include_directories(${PROJECT_SOURCE_DIR} "json/include/")

file(GLOB CPP "*.cpp")

add_executable(${PROJECT_NAME} ${CPP})