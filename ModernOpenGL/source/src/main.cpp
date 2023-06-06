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
	Mesh* cottMesh = rManager.createR<Mesh>("Cottage.obj");
	Mesh* catMesh = rManager.createR<Mesh>("Cat.obj");

	// Load Shaders
	Shader* cottShader = rManager.createR<Shader>("testShader");
	Shader* catShader = rManager.createR<Shader>("shadCat");

	// Load Textures
	Texture* cottTex = rManager.createR<Texture>("Cottage_Clean_Base_Color.png");
	Texture* cottTexBump = rManager.createR<Texture>("Cottage_Clean_MetallicSmoothness.png");
	Texture* catTex = rManager.createR<Texture>("Cat_diffuse.jpg");
	Texture* catTexBump = rManager.createR<Texture>("Cat_bump.jpg");

	// Make Models
	Model cottage; cottage.makeModel(cottTex, cottMesh, cottShader);
	Model cat; cat.makeModel(catTex, catMesh, catShader);

	// Make Entities
	Entity catE(cat);
	catE.transform.setLocalPosition(vec3(0.f, 0.f, -1.f));
	catE.transform.setLocalScale(vec3(.01f));
	catE.transform.setLocalRotation(vec3(90.f, 0.f, 0.f));
	catE.updateSelfAndChild();

	Entity cottageE(cottage);
	cottageE.transform.setLocalPosition(vec3(0.f, 0.f, -10.f));
	cottageE.transform.setLocalScale(vec3(1.f));
	cottageE.transform.setLocalRotation(vec3(0.f, -90.f, 0.f));
	cottageE.updateSelfAndChild();

	cottageE.addChild(catE);

	cottShader->use();
	cottShader->setInt("material.diffuse", cottTex->ID - 1);
	cottShader->setInt("material.specular", cottTexBump->ID - 1);
	cottShader->setFloat("material.shininess", 32.f);
	cottShader->setInt("nbSpotLight", 1);

	catShader->use();
	catShader->setInt("material.diffuse", catTex->ID - 1);
	catShader->setInt("material.specular", catTexBump->ID - 1);
	catShader->setFloat("material.shininess", 10.f);
	catShader->setInt("nbSpotLight", 1);

	SpotLight spotLight = makeSpotLight(cam.position, cam.front,
		cos(Maths::deg2Rad(12.5f)), cos(Maths::deg2Rad(15.f)),
		1.f, .09f, .032f, vec3(0.f), vec3(1.f), vec3(1.f));

	catTexBump->use();
	cottTexBump->use();

	// Main loop
	while (!glfwWindowShouldClose(app->window))
	{
		// Input
		app->processInput(cam);
		// Rendering
		glClearColor(0.f, .6f, .6f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		spotLight.position = cam.position;
		spotLight.direction = cam.front;

		mat4 VP = cam.getPerspective() * cam.getView();

		cottShader->use();
		cottShader->setVec3("viewPos", cam.position);
		cottShader->setSpotLight(spotLight, 0);
		cottShader->setMat4("VP", VP);
		cottageE.transform.computeModelMatrix();
		cottShader->setMat4("model", cottageE.transform.getModelMatrix());

		catShader->use();
		catShader->setVec3("viewPos", cam.position);
		catShader->setSpotLight(spotLight, 0);
		catShader->setMat4("VP", VP);
		catE.transform.computeModelMatrix();
		catShader->setMat4("model", catE.transform.getModelMatrix());

		cottageE.transform.setLocalRotation(vec3(0.f, cottageE.transform.getLocalRotation().y + 20.f * app->deltaTime, 0.f));
		cottageE.updateSelfAndChild();

		Entity* lastEntity = &cottageE;
		while (lastEntity->children.size())
		{
			lastEntity->drawSelfAndChild();
			lastEntity = lastEntity->children.back();
		}

		// Check and call events && then swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(app->window);
	}

	delete app;
	return EXIT_SUCCESS;
}