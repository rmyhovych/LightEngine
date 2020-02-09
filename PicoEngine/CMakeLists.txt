# Add source to this project's executable.

add_executable (PICO_ENGINE "main.cpp")

target_link_libraries (PICO_ENGINE PICO_FRAMEWORK)

message("PATH : " 	${PICO_FRAMEWORK_PATH})
target_include_directories (
	PICO_ENGINE
	
	PUBLIC

	${PICO_FRAMEWORK_PATH}	
)