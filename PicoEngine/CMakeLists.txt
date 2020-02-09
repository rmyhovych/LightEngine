# Add source to this project's executable.

add_executable (PICO_ENGINE "main.cpp")

if (NOT DEFINED GLM_PATH)
	message( FATAL_ERROR "GLM_PATH not defined." )
endif()

if (NOT DEFINED BULLET_PATH)
	message( FATAL_ERROR "BULLET_PATH not defined." )
endif()

if (NOT DEFINED PICO_FRAMEWORK_PATH)
	message( FATAL_ERROR "PICO_FRAMEWORK_PATH not defined." )
endif()

target_include_directories (
	PICO_ENGINE
	
	PUBLIC

	${GLM_PATH}
	${BULLET_PATH}
	#${PICO_FRAMEWORK_PATH}
	"../PicoFramework"

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
