#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include "debug.hpp"
#include "../include/basicmath.hpp"
#include "../include/camera.hpp"

namespace Core
{
	struct MouseInput
	{
		bool firstMouse = true;
		float lastX = 0.f, lastY = 0.f;
		float xOffset = 0.f, yOffset = 0.f;
		float scroll = 0.f;
	};

	class Application
	{
	public:
		Application(int width = 800, int height = 600);
		~Application();

		int width, height;
		GLFWwindow* window;
		float deltaTime = 0.f;

		void processInput(LowRenderer::Camera* cam);
	private:
		float lastFrame = 0.f;
	};
}