#include <iostream>

#include "FileReader.h"

#include "Window.h"
#include "ObjectManager/ObjectManager.h"
#include "Graphics/GLProgram.h"
#include "File/FileReaderHandler.h"

int main()
{
	FileReader* reader = new FileReader("C:/Users/rmyho/Desktop/PicoEngine/data/");
	FileReaderHandler::setFileReader(reader);

	Window window(1000, 500);

	GLProgram program("shaders/vertex.glsl", "shaders/fragment.glsl");

	while (window.isOpen())
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.swapBuffers();
	}

	FileData* fd = new FileData();

	return 0;
}