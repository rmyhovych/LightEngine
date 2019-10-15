cmake_minimum_required(VERSION 3.9)


include_directories(./)

if (NOT ANDROID_ES)
	find_package(GLEW REQUIRED)
	if (GLEW_FOUND)
		include_directories(${GLEW_INCLUDE_DIRS})
		link_libraries(${GLEW_LIBRARIES})
	endif()
endif()


set(PICO_ENGINE_HDRS
    gl.h

    File/FileData.h
    File/FileReaderHandler.h
    File/IFileReader.h

    Graphics/GLProgram.h
    Graphics/Shader.h
    Graphics/UniformHandling.h

    ObjectManager/Object/GraphicalObject.h
    ObjectManager/Object/Object.h
    ObjectManager/BoxManager.h
    ObjectManager/GraphicalManager.h
    ObjectManager/ObjectManager.h
    ObjectManager/PhantomManagerE.h
    ObjectManager/PhantomManagerV.h
    ObjectManager/SphereManager.h

    World/Camera.h
    World/DirLight.h
    World/PhysicalWorld.h
)

set(PICO_ENGINE_SRC

    File/FileData.cpp
    File/FileReaderHandler.cpp
    File/IFileReader.cpp

    Graphics/GLProgram.cpp
    Graphics/Shader.cpp

    ObjectManager/Object/GraphicalObject.cpp
    ObjectManager/Object/Object.cpp
    ObjectManager/BoxManager.cpp
    ObjectManager/GraphicalManager.cpp
    ObjectManager/ObjectManager.cpp
    ObjectManager/PhantomManagerE.cpp
    ObjectManager/PhantomManagerV.cpp
    ObjectManager/SphereManager.cpp

    World/Camera.cpp
    World/DirLight.cpp
    World/PhysicalWorld.cpp
)

set(GLM_PATH C:/Users/rmyho/Documents/Libraries/glm-0.9.9.6/glm/glm)

add_library(PicoEngine SHARED ${PICO_ENGINE_SRC} ${PICO_ENGINE_HDRS})
target_include_directories(PicoEngine PUBLIC ${GLM_PATH})