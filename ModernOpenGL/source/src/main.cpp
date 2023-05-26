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
	Model* modelTest = rManager.createR<Model>("Viking.obj");
	//Model* modelTest = rManager.createR<Model>("Cat.obj");

	// Load Shaders
	Shader* testShader = rManager.createR<Shader>("testShader");
	//testShader->setVertexS(rManager.findPath("test2"), true);

	// Load Textures
	//Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	//Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");
	Texture* vikingTex = rManager.createR<Texture>("viking.png");

	testShader->use();
	testShader->setInt("texture1", 0);
	//testShader->setInt("texture2", 1);

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput(&cam);

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// bind textures on corresponding texture units
		//wallTex->use(GL_TEXTURE0);
		//smileyTex->use(GL_TEXTURE1);
		vikingTex->use(GL_TEXTURE0);

		// Activate Shaders
		testShader->use();

		mat4 VP = cam.getPerspectivematrix() * cam.getViewmatrix();
		mat4 model = mat::scale(vec3(2.f, 2.f, 2.f));
		model *= mat::rotateZ(-90.f);
		model *= mat::rotateY(-90.f);
		testShader->setmat4("MVP", VP * model);

		// Draw Obj
		modelTest->draw();

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}
	delete testShader;
	//delete wallTex;
	//delete smileyTex;
	delete modelTest;
	delete vikingTex;

	delete app;
	return EXIT_SUCCESS;
}