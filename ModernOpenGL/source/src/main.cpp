#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include "../include/debug.hpp"
#include "../include/resourceManager.hpp"
#include "../include/model.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Screen Size
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main()
{
	static Log log;
	ResourceManager rManager;

	Model* tree = rManager.createR<Model>("Tree.obj");

	//return 0;
	glfwInit();
	
	// Window config
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "ModernOpenGL", NULL, NULL);
	if (!window)
	{
		DEBUG_LOG("Failed to create GLFW window");
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG_LOG("Failed to initialize GLAD");
		return EXIT_FAILURE;
	}

	// Load Shader
	Shader* testShader = rManager.createR<Shader>("testShader");
	//testShader->setVertexS(rManager.findPath("test2"), true);

	// Load Textures
	Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");

	// Triangle vertices
	float vertices[] = {
	//		  POS	    ||	   COL		||   UV
		 .5f, -.5f, 0.f,  1.f, 0.f, 0.f,  2.f, 0.f, // bottom right
		-.5f, -.5f, 0.f,  0.f, 1.f, 0.f,  0.f, 0.f, // bottom left
		 0.f,  .5f, 0.f,  0.f, 0.f, 1.f,  .5f, 2.f, // top
	};
		//unsigned int indices[] = {
		//	0, 1, 3,   // first triangle
		//	1, 2, 3,   // second triangle
		//};

	unsigned int VBO, VAO;
		// , EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
		//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	testShader->use();
	glUniform1i(glGetUniformLocation(testShader->ID, "texture1"), 0);
	testShader->setInt("texture2", 1);

	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		wallTex->use(GL_TEXTURE0);
		smileyTex->use(GL_TEXTURE1);

		// Drawing triangle
		testShader->use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
			//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
		//glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return EXIT_SUCCESS;
}

// Process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

// GLFW: whenever the window size changed (by OS or user resize) this callback function executes
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}