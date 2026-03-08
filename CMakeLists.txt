cmake_minimum_required(VERSION 3.5)

project(PacmanGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(GameFramework)
add_subdirectory(Game)
