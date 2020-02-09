cmake_minimum_required (VERSION 3.8)

project (PICO_ENGINE VERSION 1.0)

get_filename_component (PICO_FRAMEWORK_PATH PicoFramework REALPATH)


set(PICO_FRAMEWORK_PATH ${PICO_FRAMEWORK_PATH}/)

# BULLET
set (BULLET_VERSION 2.89)
set (BULLET_PATH "lib/bullet-2.89")
add_subdirectory(${BULLET_PATH})

# GLM
set (GLM_PATH "lib/glm-0.9.9.6")

# Include sub-projects.
add_subdirectory (PicoFramework)
add_subdirectory (PicoEngine)
