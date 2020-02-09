cmake_minimum_required (VERSION 3.8)

project (PICO_ENGINE VERSION 1.0)

set (PICO_FRAMEWORK_PATH )
get_filename_component (PICO_FRAMEWORK_PATH PicoFramework/src REALPATH)

# Include sub-projects.
add_subdirectory (PicoFramework)
add_subdirectory (PicoEngine)
