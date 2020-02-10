cmake_minimum_required (VERSION 3.8)

set(PICO_FRAMEWORK_HDRS
    gl.h

    File/FileData.h
    File/FileReaderHandler.h
    File/IFileReader.h

    Graphics/GLProgram.h
    Graphics/Shader.h
    Graphics/UniformHandling.h

    ObjectManager/Object/ObjectRenderer.h
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

set(PICO_FRAMEWORK_SRC

    File/FileData.cpp
    File/FileReaderHandler.cpp
    File/IFileReader.cpp

    Graphics/GLProgram.cpp
    Graphics/Shader.cpp

    ObjectManager/Object/ObjectRenderer.cpp
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


# Main Library
add_library(PICO_FRAMEWORK STATIC ${PICO_FRAMEWORK_SRC} ${PICO_FRAMEWORK_HDRS})

target_include_directories(
	PICO_FRAMEWORK

	PUBLIC

	./
	${BULLET_PATH}
	${GLM_PATH}
	${GL3W_INCLUDE_PATH}
)

target_link_libraries(
	PICO_FRAMEWORK

	BulletCollision
	BulletDynamics
	LinearMath

	gl3w
)