#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include "../include/debug.hpp"
#include "../include/resourceManager.hpp"
#include "../include/model.hpp"
#include "../include/application.hpp"
#include "../include/camera.hpp"
#include "../include/light.hpp"

using namespace Core;
using namespace LowRenderer;
using namespace Resources;

int main()
{
	static Debug::Log log;
	Application* app = new Application();
	Camera cam(app->width, app->height);
	ResourceManager rManager;

	//Mesh* meshTest = rManager.createR<Mesh>("Tree.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Viking.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Cat.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("WeirdCat.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Cottage.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Bench.obj");
	Mesh* meshTest = rManager.createR<Mesh>("Horse.obj");

	// Load Shaders
	Shader* testShader = rManager.createR<Shader>("testShader");
	Shader* testLight = rManager.createR<Shader>("testLight");

	// Load Textures
	//Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	//Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");
	//Texture* vikingTex = rManager.createR<Texture>("viking.png");
	//Texture* catTex = rManager.createR<Texture>("Cat_diffuse.jpg");
	//Texture* catTexBump = rManager.createR<Texture>("Cat_bump.jpg");
	Texture* cottTex = rManager.createR<Texture>("Cottage_Clean_Base_Color.png");
	Texture* cottTexBump = rManager.createR<Texture>("Cottage_Clean_Roughness.png");

	// Make Model
	Model cottage; cottage.makeModel(cottTex, meshTest);

	float vertices[] = {
		-.5f, -.5f, -.5f,
		 .5f, -.5f, -.5f,
		 .5f,  .5f, -.5f,
		 .5f,  .5f, -.5f,
		-.5f,  .5f, -.5f,
		-.5f, -.5f, -.5f,

		-.5f, -.5f,  .5f,
		 .5f, -.5f,  .5f,
		 .5f,  .5f,  .5f,
		 .5f,  .5f,  .5f,
		-.5f,  .5f,  .5f,
		-.5f, -.5f,  .5f,

		-.5f,  .5f,  .5f,
		-.5f,  .5f, -.5f,
		-.5f, -.5f, -.5f,
		-.5f, -.5f, -.5f,
		-.5f, -.5f,  .5f,
		-.5f,  .5f,  .5f,

		 .5f,  .5f,  .5f,
		 .5f,  .5f, -.5f,
		 .5f, -.5f, -.5f,
		 .5f, -.5f, -.5f,
		 .5f, -.5f,  .5f,
		 .5f,  .5f,  .5f,

		-.5f, -.5f, -.5f,
		 .5f, -.5f, -.5f,
		 .5f, -.5f,  .5f,
		 .5f, -.5f,  .5f,
		-.5f, -.5f,  .5f,
		-.5f, -.5f, -.5f,

		-.5f,  .5f, -.5f,
		 .5f,  .5f, -.5f,
		 .5f,  .5f,  .5f,
		 .5f,  .5f,  .5f,
		-.5f,  .5f,  .5f,
		-.5f,  .5f, -.5f,
	};

	unsigned int lightCubeVAO, lightCubeVBO;
	glGenBuffers(1, &lightCubeVBO);
	glGenVertexArrays(1, &lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(lightCubeVAO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	testShader->use();
	testShader->setInt("material.diffuse", 0);
	testShader->setInt("material.specular", 1);

	vec3 lightPos(1.2f, 1.f, 2.f);

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput(&cam);

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind textures
		//wallTex->use(GL_TEXTURE0);
		//smileyTex->use(GL_TEXTURE1);
		//vikingTex->use(GL_TEXTURE0);
		//catTex->use(GL_TEXTURE0);
		//catTexBump->use(GL_TEXTURE1);
		//cottTex->use(GL_TEXTURE0);
		cottTexBump->use(GL_TEXTURE1);

		mat4 VP = cam.getPerspective() * cam.getView();

		lightPos.x = 1.f + sin((float)glfwGetTime()) * 2.f;
		lightPos.z = sin((float)glfwGetTime() / 2.f) * 1.f;

		testLight->use();
		glBindVertexArray(lightCubeVAO);
		mat4 modelLight = Maths::mat::translate(lightPos);
		modelLight *= Maths::mat::scale(vec3(.2f));
		testLight->setMat4("MVP", VP * modelLight);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		// Activate Shaders
		testShader->use();
		//testShader->setVec3("lightColor", lightColor);
		testShader->setVec3("lightPos", lightPos);
		testShader->setVec3("viewPos", cam.position);
		testShader->setFloat("material.shininess", 32.f);

		testShader->setInt("nbDirLight", 0);
		// point light
		testShader->setPointLight(makePointLight(lightPos, 1.f, .09f, .032f,
			vec3(.05f), vec3(.8f), vec3(1.f)), 0);

		// spotLight
		testShader->setSpotLight(makeSpotLight(cam.position, cam.front,
			cos(Maths::deg2Rad(12.5f)), cos(Maths::deg2Rad(15.f)),
			1.f, .09f, .032f, vec3(0.f), vec3(1.f), vec3(1.f)), 0);

		// Create MVP matrix
		mat4 model = Maths::mat::scale(vec3(1.f));
		//model *= Maths::mat::rotateZ(-90.f);
		model *= Maths::mat::rotateY(-90.f);
		testShader->setMat4("model", model);
		testShader->setMat4("VP", VP);

		// Draw Obj
		cottage.draw(GL_TEXTURE0);

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}
	delete app;
	return EXIT_SUCCESS;
}