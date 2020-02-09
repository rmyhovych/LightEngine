# Add source to this project's executable.

add_executable (PICO_ENGINE "main.cpp")

if (NOT DEFINED GLM_PATH)
	set (GLM_PATH "lib/glm-0.9.9.6")
endif()

if (NOT DEFINED BULLET_PATH)
	if (NOT DEFINED BULLET_VERSION)
		set (BULLET_VERSION 2.89)
	endif()

	set (BULLET_PATH "lib/bullet-2.89")
	add_subdirectory(${BULLET_PATH})
endif()

if (NOT DEFINED PICO_FRAMEWORK_PATH)
	message( FATAL_ERROR "PICO_FRAMEWORK_PATH not defined." )
endif()

target_include_directories (
	PICO_ENGINE
	
	PUBLIC

	${GLM_PATH}
	${BULLET_PATH}
	${PICO_FRAMEWORK_PATH}

	"lib/glew-2.1.0/include"
)

target_link_libraries (
	PICO_ENGINE 

	PICO_FRAMEWORK
	BulletCollision
	BulletDynamics
	LinearMath

	"lib/glew-2.1.0/lib/Release/x64"
)
