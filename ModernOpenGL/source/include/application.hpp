#ifndef APPLICATION_H
#define APPLICATION_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include "debug.hpp"

class Application
{
public:
	Application(int width = 800, int height = 600);
	~Application();

	int width, height;
	GLFWwindow* window;

	void processInput();
private:
};
#endif