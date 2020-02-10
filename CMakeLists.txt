cmake_minimum_required (VERSION 3.8)

project (PICO_ENGINE VERSION 1.0)

# PICO FRAMEWORK
get_filename_component (PICO_FRAMEWORK_PATH PicoFramework REALPATH)

# BULLET
set (BULLET_VERSION 2.89)
get_filename_component (BULLET_PATH lib/bullet-2.89 REALPATH)
add_subdirectory(${BULLET_PATH})

# GLM
get_filename_component (GLM_PATH lib/glm-0.9.9.6 REALPATH)

# Include sub-projects.
add_subdirectory (PicoFramework)
add_subdirectory (PicoEngine)
