cmake_minimum_required(VERSION 3.30)
project(avl_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(avl_tree main.cpp
        AVL.h
        LicensePlate.h
        app.h
)
