#pragma once

#include "basicmath.hpp"

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace LowRenderer
{
	class Camera
	{
	public:
		Camera(int width, int height);
		~Camera() {};

		void processInput(GLFWwindow* window, float deltaTime);
		void processMouse(float xoffset, float yoffset);
		void ProcessScroll(float yoffset);

		void setPosition(vec3 newPos);

		mat4 getViewmatrix();
		mat4 getPerspectivematrix();

		float speed = 6.f;

	private:
		vec3 position = { 0.f,0.f,5.f };
		vec3 front = { 0.f,0.f,-1.f };
		vec3 up = { 0.f,1.f,0.f };
		vec3 right, worldUp = up;

		float pitch = 0.f, yaw = -90.f;
		float sensitivity = .1f, zoom = 45.f;
		float near_ = .1f, far_ = 100.f, aspect;

		void updateCameraVectors();
	};
}