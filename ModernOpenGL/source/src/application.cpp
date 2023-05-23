#include "../include/application.hpp"

void framebufferSizeCallback(GLFWwindow* window, int width, int height);

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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG_LOG("Failed to initialize GLAD");
		exit(EXIT_FAILURE);
	}
}

Application::~Application()
{
	glfwTerminate();
}

void Application::processInput()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}