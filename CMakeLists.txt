cmake_minimum_required(VERSION 3.10)

project(Caesar)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES caesar.cpp)


add_executable(Caesar ${SOURCES})

