#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include "../include/debug.hpp"
#include "../include/resourceManager.hpp"
#include "../include/model.hpp"
#include "../include/application.hpp"
#include "../include/camera.hpp"

int main()
{
	static Log log;
	Application* app = new Application();
	Camera cam(app->width, app->height);
	ResourceManager rManager;

	//Model* modelTest = rManager.createR<Model>("Tree.obj");
	//Model* modelTest = rManager.createR<Model>("Viking.obj");
	//Model* modelTest = rManager.createR<Model>("Cat.obj");
	
	float vertices[] = {
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 0.f,
		.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  1.f, 0.f,
		.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
		.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
	   -.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 0.f,
										  
	   -.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
		.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 1.f,
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 1.f,
	   -.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  0.f, 1.f,
	   -.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
										  
	   -.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
	   -.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
	   -.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
	   -.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
										  
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
		.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
		.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
		.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
		.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
										  
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
		.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
		.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
		.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
	   -.5f, -.5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
	   -.5f, -.5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
						  				  
	   -.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f,
		.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  1.f, 1.f,
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
		.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  1.f, 0.f,
	   -.5f,  .5f,  .5f,  0.f, 0.f, 0.f,  0.f, 0.f,
	   -.5f,  .5f, -.5f,  0.f, 0.f, 0.f,  0.f, 1.f
	};
	vec3 cubePositions[] = {
		vec3(0.f,  0.f,  0.f),
		vec3(2.f,  5.f, -15.f),
		vec3(-1.5f, -2.2f, -2.5f),
		vec3(-3.8f, -2.f, -12.3f),
		vec3(2.4f, -.4f, -3.5f),
		vec3(-1.7f,  3.f, -7.5f),
		vec3(1.3f, -2.f, -2.5f),
		vec3(1.5f,  2.f, -2.5f),
		vec3(1.5f,  .2f, -1.5f),
		vec3(-1.3f,  1.f, -1.5f)
	};
	/*
	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	};
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3,   // second triangle
	};*/

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Load Shaders
	Shader* testShader = rManager.createR<Shader>("testShader");
	//testShader->setVertexS(rManager.findPath("test2"), true);

	// Load Textures
	Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");

	testShader->use();
	testShader->setInt("texture1", 0);
	testShader->setInt("texture2", 1);

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput(&cam);

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		wallTex->use(GL_TEXTURE0);
		smileyTex->use(GL_TEXTURE1);

		// Activate Shaders
		testShader->use();

		//const float radius = 10.0f;
		//float camX = sin(glfwGetTime()) * radius;
		//float camZ = cos(glfwGetTime()) * radius;
		//cam.setPosition({ camX, 0.f, camZ });

		glm::mat4 VP = cam.getPerspectivematrix() * cam.getViewmatrix();

		glBindVertexArray(VAO);
		for (unsigned int i = 0; i < 10; i++)
		{
			mat4 trueVP = {
				VP[0][0], VP[0][1], VP[0][2], VP[0][3],
				VP[1][0], VP[1][1], VP[1][2], VP[1][3],
				VP[2][0], VP[2][1], VP[2][2], VP[2][3],
				VP[3][0], VP[3][1], VP[3][2], VP[3][3]
			};
			mat4 model = mat::translate(cubePositions[i]);

			float angle = 20.f * i;
			model *= mat::rotate(angle, vec3(1.f, .3f, .5f));

			glm::mat4 trueModel = {
				model.v[0].x, model.v[1].x, model.v[2].x, model.v[3].x,
				model.v[0].y, model.v[1].y, model.v[2].y, model.v[3].y,
				model.v[0].z, model.v[1].z, model.v[2].z, model.v[3].z,
				model.v[0].w, model.v[1].w, model.v[2].w, model.v[3].w
			};
			glm::mat4 MVP = VP * trueModel;
			//cout << "glm:" << endl;
			//for (int i = 0; i < 4; i++) {
			//	for (int j = 0; j < 4; j++)
			//		cout << testMVP[i][j] << " | ";
			//	cout << '\n';
			//}

			//mat4 MVP = model * trueVP;
			//cout << "MOI:" << endl << MVP << endl;

			mat4 trueMVP = {
			   MVP[0][0], MVP[0][1], MVP[0][2], MVP[0][3],
			   MVP[1][0], MVP[1][1], MVP[1][2], MVP[1][3],
			   MVP[2][0], MVP[2][1], MVP[2][2], MVP[2][3],
			   MVP[3][0], MVP[3][1], MVP[3][2], MVP[3][3]
			};
			testShader->setmat4("MVP", trueMVP);

			glDrawArrays(GL_TRIANGLES, 0, 36);
		}/*
		mat4 MVP = VP;
		testShader->setmat4("MVP", MVP);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);*/

		// Draw Obj
		//modelTest->draw();

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}
	delete testShader;
	delete wallTex;
	delete smileyTex;
	//delete modelTest;

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);

	delete app;
	return EXIT_SUCCESS;
}

/*
int main()
{
	static Log log;
	Application* app = new Application();
	ResourceManager rManager;

	//Model* modelTest = rManager.createR<Model>("Tree.obj");
	//Model* modelTest = rManager.createR<Model>("Viking.obj");
	//Model* modelTest = rManager.createR<Model>("Cat.obj");

	// Load Shaders
	Shader* testShader = rManager.createR<Shader>("testShader");
	//testShader->setVertexS(rManager.findPath("test2"), true);

	// Load Textures
	Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");

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
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
*/