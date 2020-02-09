cmake_minimum_required (VERSION 3.8)

# Bullet Physics
set(BULLET_VERSION 2.89)
add_subdirectory(${BULLET_PATH})

# GLEW for Windows
#if (NOT ANDROID_ES)
#	target_include_directories(PICO_ENGINE PUBLIC "glew-2.1.0/include")
#	target_link_libraries(PICO_ENGINE PUBLIC "glew-2.1.0/lib/Release/x64")
#endif()
