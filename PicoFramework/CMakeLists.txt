cmake_minimum_required (VERSION 3.8)

get_filename_component (BULLET_PATH dependencies/bullet-2.89 REALPATH)
get_filename_component (GLEW_PATH dependencies/glew-2.1.0 REALPATH)
get_filename_component (GLM_PATH dependencies/glm-0.9.9.6 REALPATH)

add_subdirectory(dependencies)

# PICO FRAMEWORK
add_subdirectory(src)
