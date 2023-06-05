#include "../include/shader.hpp"
#include "../include/texture.hpp"
#include "../include/debug.hpp"
#include "../include/resourceManager.hpp"
#include "../include/model.hpp"
#include "../include/application.hpp"
#include "../include/camera.hpp"
#include "../include/light.hpp"
#include "../include/entity.hpp"

using namespace Core;
using namespace Physics;
using namespace LowRenderer;
using namespace Resources;
using namespace Maths::mat;

int main()
{
	static Debug::Log log;
	Application* app = new Application();
	Camera cam(app->width, app->height);
	ResourceManager rManager;

	// Load Meshes
	//Mesh* meshTest = rManager.createR<Mesh>("Tree.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Viking.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("WeirdCat.obj");
	Mesh* cottMesh = rManager.createR<Mesh>("Cottage.obj");
	Mesh* catTest = rManager.createR<Mesh>("Cat.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Bench.obj");
	//Mesh* meshTest = rManager.createR<Mesh>("Horse.obj");

	// Load Shaders
	Shader* cottShader = rManager.createR<Shader>("testShader");
	Shader* catShader = cottShader;
	//Shader* testLight = rManager.createR<Shader>("testLight");

	// Load Textures
	//Texture* wallTex = rManager.createR<Texture>("wall.jpg");
	//Texture* smileyTex = rManager.createR<Texture>("awesomeface.png");
	//Texture* vikingTex = rManager.createR<Texture>("viking.png");
	Texture* cottTex = rManager.createR<Texture>("Cottage_Clean_Base_Color.png");
	Texture* cottTexBump = rManager.createR<Texture>("Cottage_Clean_MetallicSmoothness.png");
	Texture* catTex = rManager.createR<Texture>("Cat_diffuse.jpg");
	Texture* catTexBump = rManager.createR<Texture>("Cat_bump.jpg");

	// Make Models
	Model cottage; cottage.makeModel(cottTex, cottMesh);
	Model cat; cat.makeModel(catTex, catTest);

	// Make Entities
	Entity cottageE(cottage);
	cottageE.transform.setLocalPosition(vec3(10.f, 0.f, 0.f));
	cottageE.transform.setLocalScale(vec3(.5f));
	cottageE.transform.setLocalRotation(vec3(.0f, -90.f, 0.f));
	cottageE.updateSelfAndChild();

	Entity catE(cat);
	catE.transform.setLocalPosition(vec3(0.f, 0.f, 10.f));
	catE.transform.setLocalScale(vec3(.1f));
	catE.transform.setLocalRotation(vec3(.0f, -90.f, 0.f));
	catE.updateSelfAndChild();

	cottageE.addChild(catE);

	cottShader->use();
	cottShader->setInt("material.diffuse", 0);
	cottShader->setInt("material.specular", 1);
	cottShader->setFloat("material.shininess", 32.f);

	catShader->use();
	catShader->setInt("material.diffuse", 2);
	catShader->setInt("material.specular", 3);
	catShader->setFloat("material.shininess", 10.f);

	SpotLight spotLight = makeSpotLight(cam.position, cam.front,
		cos(Maths::deg2Rad(12.5f)), cos(Maths::deg2Rad(15.f)),
		1.f, .09f, .032f, vec3(0.f), vec3(1.f), vec3(1.f));

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput(cam);

		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Bind textures
		//wallTex->use();
		//smileyTex->use();
		//vikingTex->use();
		//catTex->use();
		catTexBump->use();//try outside loop TODO
		//cottTex->use();
		cottTexBump->use();

		// Activate Shaders
		cottShader->use();
		catShader->use();
		cottShader->setVec3("viewPos", cam.position);
		catShader->setVec3("viewPos", cam.position);

		// spotLight
		cottShader->setInt("nbSpotLight", 1);
		catShader->setInt("nbSpotLight", 1);
		spotLight.position = cam.position;
		spotLight.direction = cam.front;
		cottShader->setSpotLight(spotLight, 0);
		catShader->setSpotLight(spotLight, 0);

		// Create MVP matrix
		mat4 VP = cam.getPerspective() * cam.getView();
		cottShader->setMat4("VP", VP);
		catShader->setMat4("VP", VP);

		cottageE.transform.computeModelMatrix();
		cottShader->setMat4("model", cottageE.transform.getModelMatrix());

		catE.transform.computeModelMatrix();
		catShader->setMat4("model", catE.transform.getModelMatrix());

		cottageE.transform.setLocalRotation(vec3(0.f, cottageE.transform.getLocalRotation().y + 20.f * app->deltaTime, 0.f));
		cottageE.updateSelfAndChild();

		// Draw Obj
		cottageE.drawSelfAndChild();

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}

	delete app;
	return EXIT_SUCCESS;
}