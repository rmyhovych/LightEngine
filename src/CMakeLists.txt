CMAKE_MINIMUM_REQUIRED(VERSION 3.9)

INCLUDE_DIRECTORIES(./)

SET(PICO_ENGINE_HDRS
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

SET(PICO_ENGINE_SRC

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

ADD_LIBRARY(PicoEngine SHARED ${PICO_ENGINE_SRC} ${PICO_ENGINE_HDRS})