#include <iostream>

#include "FileReader.h"

#include "Window.h"
#include "ObjectManager/ObjectManager.h"
#include "Graphics/GLProgram.h"
#include "File/FileReaderHandler.h"
#include "World/Camera.h"

#include "World/PhysicalWorld.h"

int main()
{
	FileReader* reader = new FileReader("C:/Users/rmyho/Desktop/PicoEngine/data/");
	FileReaderHandler::setFileReader(reader);


	const int width = 1000;
	const int height = 500;
	Window window(width, height);

	Camera camera(width, height, 20);

	GLProgram program("shaders/vertex/vertex_base.glsl", "shaders/fragment/fragment_base.glsl");
	ObjectManager* om = program.addBoxManager();
	Object* obj = om->createObject(10);
	obj->rotate(btQuaternion(btVector3(1, 0.5, 0.2), 5));
	obj->setPosition(btVector3(0, 10, 0));

	Object* obj2 = om->createObject(0, 0, 0, glm::vec3(0, -5, 0), glm::vec3(1), glm::vec3(5, 0.1, 5));

	glm::vec3 light(1, -2, 1.5);

	while (window.isOpen())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		obj->push(btVector3(0, -20, 0));

		PhysicalWorld::getInstance()->step(60);
		program.render(light, camera.getPV());

		window.swapBuffers();
	}

	FileData* fd = new FileData();

	return 0;
}