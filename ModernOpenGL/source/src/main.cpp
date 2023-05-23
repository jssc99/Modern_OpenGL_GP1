#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include "../include/debug.hpp"
#include "../include/resourceManager.hpp"
#include "../include/model.hpp"
#include "../include/application.hpp"

int main()
{
	static Log log;
	Application* app = new Application();
	ResourceManager rManager;

	Model* modelTest = rManager.createR<Model>("Tree.obj");
	//Model* modelTest = rManager.createR<Model>("Viking.obj");
	//Model* modelTest = rManager.createR<Model>("Cat.obj");

	// Load Shaders
	Shader* testShader = rManager.createR<Shader>("testShader");
	testShader->setVertexS(rManager.findPath("test2"), true);

	// Load Textures
	Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");
	/*
	// Triangle vertices
	float vertices[] = {
		//	   POS	    ||	   COL		||   UV
		 .5f, -.5f, 0.f,  1.f, 0.f, 0.f,  2.f, 0.f, // bottom right
		-.5f, -.5f, 0.f,  0.f, 1.f, 0.f,  0.f, 0.f, // bottom left
		-.5f,  .5f, 0.f,  1.f, 0.f, 1.f,  1.f, 2.f, // top left
		 .5f,  .5f, 0.f,  0.f, 0.f, 1.f,  .5f, 2.f, // top right
	};
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

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

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	testShader->use();
	glUniform1i(glGetUniformLocation(testShader->ID, "texture1"), 0);
	testShader->setInt("texture2", 1);

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput();

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		// bind textures on corresponding texture units
		wallTex->use(GL_TEXTURE0);
		smileyTex->use(GL_TEXTURE1);

		// Drawing triangle
		testShader->use();
		modelTest->draw();
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glBindVertexArray(0);

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	
	delete app;
	delete testShader;
	delete wallTex;
	delete smileyTex;
	delete modelTest;
	return EXIT_SUCCESS;
}