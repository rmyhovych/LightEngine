cmake_minimum_required (VERSION 3.8)

project (PICO_ENGINE VERSION 1.0)

get_filename_component (PICO_FRAMEWORK_PATH PicoFramework REALPATH)


get_filename_component (GLEW_PATH lib/glew-2.1.0/ REALPATH)

list(APPEND CMAKE_PREFIX_PATH ${GLEW_PATH})

find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

message("GLEW : "${GLEW_INCLUDE_DIRS} " ... " ${GLEW_LIBRARIES})

# BULLET
set (BULLET_VERSION 2.89)
get_filename_component (BULLET_PATH lib/bullet-2.89 REALPATH)
add_subdirectory(${BULLET_PATH})

# GLM
get_filename_component (GLM_PATH lib/glm-0.9.9.6 REALPATH)

# Include sub-projects.
add_subdirectory (PicoFramework)
add_subdirectory (PicoEngine)
