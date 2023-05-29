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

	//Model* modelTest = rManager.createR<Model>("Tree.obj");
	//Model* modelTest = rManager.createR<Model>("Viking.obj");
	//Model* modelTest = rManager.createR<Model>("Cat.obj");
	Model* modelTest = rManager.createR<Model>("Cottage.obj");

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

	vec3 pointLightPositions[] = {
		vec3(0.7f,  .2f,  2.f),
		vec3(2.3f, -3.3f, -4.f),
		vec3(-4.f,  2.f, -12.f),
		vec3(0.f,  0.f, -3.f)
	};

	unsigned int lightCubeVAO, VBO;
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &lightCubeVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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
		cottTex->use(GL_TEXTURE0);
		cottTexBump->use(GL_TEXTURE1);

		mat4 VP = cam.getPerspective() * cam.getView();

		pointLightPositions[0].x = 1.f + sinf((float)glfwGetTime()) * 2.f;
		pointLightPositions[0].z = sinf((float)glfwGetTime() / 2.f) * 1.f;

		testLight->use();
		glBindVertexArray(lightCubeVAO);
		for (unsigned int i = 0; i < 4; i++)
		{
			mat4 model = Maths::mat::translate(pointLightPositions[i]);
			model *= Maths::mat::scale(vec3(.2f));
			testLight->setMat4("MVP", VP * model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		// Activate Shaders
		testShader->use();
		//testShader->setVec3("lightColor", lightColor);
		testShader->setVec3("lightPos", lightPos);
		testShader->setVec3("viewPos", cam.position);
		testShader->setFloat("material.shininess", 32.f);

		testShader->setInt("nbPointLight", 4);
		// directional light
		testShader->setVec3("dirLight[0].direction", -.2f, -1.f, -.3f);
		testShader->setVec3("dirLight[0].ambient", .05f, .05f, .05f);
		testShader->setVec3("dirLight[0].diffuse", .4f, .4f, .4f);
		testShader->setVec3("dirLight[0].specular", .5f, .5f, .5f);
		// point light 1
		testShader->setVec3("pointLights[0].position", pointLightPositions[0]);
		testShader->setVec3("pointLights[0].ambient", .05f, .05f, .05f);
		testShader->setVec3("pointLights[0].diffuse", .8f, .8f, .8f);
		testShader->setVec3("pointLights[0].specular", 1.f, 1.f, 1.f);
		testShader->setFloat("pointLights[0].constant", 1.f);
		testShader->setFloat("pointLights[0].linear", .09f);
		testShader->setFloat("pointLights[0].quadratic", .032f);
		// point light 2
		testShader->setVec3("pointLights[1].position", pointLightPositions[1]);
		testShader->setVec3("pointLights[1].ambient", .05f, .05f, .05f);
		testShader->setVec3("pointLights[1].diffuse", .8f, .8f, .8f);
		testShader->setVec3("pointLights[1].specular", 1.f, 1.f, 1.f);
		testShader->setFloat("pointLights[1].constant", 1.f);
		testShader->setFloat("pointLights[1].linear", .09f);
		testShader->setFloat("pointLights[1].quadratic", .032f);
		// point light 3
		testShader->setVec3("pointLights[2].position", pointLightPositions[2]);
		testShader->setVec3("pointLights[2].ambient", .05f, .05f, .05f);
		testShader->setVec3("pointLights[2].diffuse", .8f, .8f, .8f);
		testShader->setVec3("pointLights[2].specular", 1.f, 1.f, 1.f);
		testShader->setFloat("pointLights[2].constant", 1.f);
		testShader->setFloat("pointLights[2].linear", .09f);
		testShader->setFloat("pointLights[2].quadratic", .032f);
		// point light 4
		testShader->setVec3("pointLights[3].position", pointLightPositions[3]);
		testShader->setVec3("pointLights[3].ambient", .05f, .05f, .05f);
		testShader->setVec3("pointLights[3].diffuse", .8f, .8f, .8f);
		testShader->setVec3("pointLights[3].specular", 1.f, 1.f, 1.f);
		testShader->setFloat("pointLights[3].constant", 1.f);
		testShader->setFloat("pointLights[3].linear", .09f);
		testShader->setFloat("pointLights[3].quadratic", .032f);
		// spotLight
		testShader->setVec3("spotLight[0].position", cam.position);
		testShader->setVec3("spotLight[0].direction", cam.front);
		testShader->setVec3("spotLight[0].ambient", 0.f, 0.f, 0.f);
		testShader->setVec3("spotLight[0].diffuse", 1.f, 1.f, 1.f);
		testShader->setVec3("spotLight[0].specular", 1.f, 1.f, 1.f);
		testShader->setFloat("spotLight[0].constant", 1.f);
		testShader->setFloat("spotLight[0].linear", .09f);
		testShader->setFloat("spotLight[0].quadratic", .032f);
		testShader->setFloat("spotLight[0].cutOff", cos(Maths::deg2Rad(12.5f)));
		testShader->setFloat("spotLight[0].outerCutOff", cos(Maths::deg2Rad(15.f)));

		// Create MVP matrix
		mat4 model = Maths::mat::scale(vec3(.2f));
		//model *= Maths::mat::rotateZ(-90.f);
		model *= Maths::mat::rotateY(-90.f);
		testShader->setMat4("model", model);
		testShader->setMat4("VP", VP);

		// Draw Obj
		modelTest->draw();

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}
	delete app;
	return EXIT_SUCCESS;
}