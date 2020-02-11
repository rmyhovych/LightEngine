# Add source to this project's executable.

set (
	PICO_ENGINE_HDRS

	Window.h
	FileReader.h
)

set (
	PICO_ENGINE_SRC

	main.cpp

	Window.cpp
	FileReader.cpp
)

add_executable (
	PICO_ENGINE 
	
	${PICO_ENGINE_HDRS}
	${PICO_ENGINE_SRC}
)

if (NOT DEFINED GLM_PATH)
	message( FATAL_ERROR "GLM_PATH not defined." )
endif()

if (NOT DEFINED BULLET_PATH)
	message( FATAL_ERROR "BULLET_PATH not defined." )
endif()

if (NOT DEFINED PICO_FRAMEWORK_PATH)
	message( FATAL_ERROR "PICO_FRAMEWORK_PATH not defined." )
endif()

find_package(OpenGL REQUIRED)

target_include_directories (
	PICO_ENGINE
	
	PUBLIC

	${GLM_PATH}
	${BULLET_PATH}
	${PICO_FRAMEWORK_PATH}

	../lib/glfw-3.3.2/include
)

target_link_libraries (
	PICO_ENGINE 

	PICO_FRAMEWORK
	BulletCollision
	BulletDynamics
	LinearMath

	OpenGL::GL
	C:/Users/rmyho/Desktop/PicoEngine/lib/glfw-3.3.2/lib-vc2019/glfw3.lib
)
