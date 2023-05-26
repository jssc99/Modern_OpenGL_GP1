#include "../include/application.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn);
void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

using namespace Core;

MouseInput mouseIn;

Application::Application(int width, int height)
{
	glfwInit();

	// Window config
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(width, height, "ModernOpenGL", NULL, NULL);
	if (!window)
	{
		DEBUG_LOG("Failed to create GLFW window");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	this->width = width; this->height = height;

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG_LOG("Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}

	glEnable(GL_DEPTH_TEST);
}

Application::~Application()
{
	glfwTerminate();
}

void Application::processInput(LowRenderer::Camera *cam)
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	// Camera updates
	cam->processInput(window, deltaTime);

	if (mouseIn.xOffset != 0.f || mouseIn.yOffset != 0.f) {
		cam->processMouse(mouseIn.xOffset, mouseIn.yOffset);
		mouseIn.xOffset = 0.f; mouseIn.yOffset = 0.f;
	}

	if (mouseIn.scroll != 0.f) {
		cam->ProcessScroll(mouseIn.scroll);
		mouseIn.scroll = 0.f;
	}
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{ // GLFW: whenever the window size changed (by OS or user resize) this callback function executes
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, double xPosIn, double yPosIn)
{
	float xPos = (float)xPosIn;
	float yPos = (float)yPosIn;

	if (mouseIn.firstMouse)
	{
		mouseIn.lastX = xPos;
		mouseIn.lastY = yPos;
		mouseIn.firstMouse = false;
	}

	mouseIn.xOffset = xPos - mouseIn.lastX;
	mouseIn.yOffset = mouseIn.lastY - yPos;

	mouseIn.lastX = xPos;
	mouseIn.lastY = yPos;
}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	mouseIn.scroll = (float)yOffset;
}