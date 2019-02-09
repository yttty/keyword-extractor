cmake_minimum_required(VERSION 3.1.0)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(KeywordExtractor)

include_directories(include)
file(GLOB SOURCES "src/*.cc")

add_executable(KeywordExtractor ${SOURCES})

