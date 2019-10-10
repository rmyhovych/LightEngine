CMAKE_MINIMUM_REQUIRED(VERSION 3.9)
project(PicoEngine VERSION 1.0.0 DESCRIPTION "Lightweight OpenGL engine.")

SUBDIRS(src)

target_include_directories(PicoEngine PRIVATE src)
