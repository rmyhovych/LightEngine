cmake_minimum_required (VERSION 3.8)

# Bullet Physics
set(BULLET_VERSION 2.89)
add_subdirectory(bullet-2.89)
include_directories(bullet-2.89)


# GLM
include_directories(glm-0.9.9.6)


# GLEW for Windows
#if (NOT ANDROID_ES)
#	target_include_directories(PICO_ENGINE PUBLIC "glew-2.1.0/include")
#	target_link_libraries(PICO_ENGINE PUBLIC "glew-2.1.0/lib/Release/x64")
#endif()


# PICO FRAMEWORK
add_subdirectory(pf)
include_directories(pf)
