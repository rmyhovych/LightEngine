cmake_minimum_required (VERSION 3.8)

add_subdirectory(dependencies)

# PICO FRAMEWORK
add_subdirectory(src)
include_directories(src)
