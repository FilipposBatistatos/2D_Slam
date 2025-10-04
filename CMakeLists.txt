cmake_minimum_required(VERSION 3.10)

project(2D_Slam)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
set(SOURCES
    src/main.cpp
    src/Maze.cpp
    src/Renderer.cpp
    src/Robot.cpp
)

add_executable(2D_Slam ${SOURCES})

target_link_libraries(2D_Slam
    sfml-graphics
    sfml-window
    sfml-system
)