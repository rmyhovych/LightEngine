cmake_minimum_required (VERSION 3.8)

project (PICO_ENGINE VERSION 1.0)

get_filename_component (PICO_FRAMEWORK_PATH PicoFramework REALPATH)

get_filename_component (GL3W_PATH lib/gl3w REALPATH)

add_subdirectory(${GL3W_PATH})
set (GL3W_INCLUDE_PATH ${GL3W_PATH}/src)

# BULLET
set (BULLET_VERSION 2.89)
get_filename_component (BULLET_PATH lib/bullet-2.89 REALPATH)
add_subdirectory(${BULLET_PATH})

# GLM
get_filename_component (GLM_PATH lib/glm-0.9.9.6 REALPATH)

# Include sub-projects.
add_subdirectory (PicoFramework)
add_subdirectory (PicoEngine)
