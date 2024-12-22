cmake_minimum_required(VERSION 3.26)
project(avl_tree)

set(CMAKE_CXX_STANDARD 20)

set(SOURCES
        main.cpp
        src/menu.cpp
        src/config.cpp
        src/path.cpp
)

set(HEADERS
        src/include/avl_tree.h
        src/include/license_plate.h
        src/include/app.h
        src/include/config.h
        src/include/menu.h
        src/include/path.h
        src/include/sllist.h
)

add_executable(avl_tree ${SOURCES} ${HEADERS})
