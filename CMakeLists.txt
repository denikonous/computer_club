cmake_minimum_required(VERSION 3.5)

project(computer_club LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(computer_club main.cpp
                             file_reader.cpp
                             calc_club.cpp
                             file_reader.h
                             calc_club.h
)
