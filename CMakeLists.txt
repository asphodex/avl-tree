cmake_minimum_required(VERSION 3.30)
project(avl_tree)

set(CMAKE_CXX_STANDARD 20)

add_executable(avl_tree main.cpp
        src/include/avl_tree.h
        src/include/license_plate.h
        src/include/App.h
        src/menu.cpp
        src/config.cpp
        src/path.cpp
        src/include/Config.h
        src/include/Menu.h
        src/include/Path.h
)
