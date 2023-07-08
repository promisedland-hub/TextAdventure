cmake_minimum_required(VERSION 3.25)
project(TextAdventure VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(Textadventure main.cpp enemy.h enemy.cpp)