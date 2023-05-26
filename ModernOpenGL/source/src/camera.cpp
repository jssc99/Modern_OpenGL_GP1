#include "../include/camera.hpp"
#include "../include/debug.hpp"

using namespace LowRenderer;
using namespace Core::Maths;

Camera::Camera(int width, int height)
{
	aspect = (float)width / height;
	updateCameraVectors();
}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * deltaTime * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= speed * deltaTime * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= normalize(cross(front, up)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += normalize(cross(front, up)) * speed * deltaTime;
}

void Camera::processMouse(float xOffset, float yOffset)
{
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	updateCameraVectors();
}

void Camera::ProcessScroll(float yOffset)
{
	zoom -= yOffset;
	if (zoom < 1.0f) zoom = 1.0f;
	if (zoom > 45.0f) zoom = 45.0f;
}

void Camera::setPosition(vec3 newPos) {
	position = newPos;
}

mat4 Camera::getViewmatrix()
{
	vec3 forward = normalize(-front);
	vec3 right = normalize(cross(normalize(up), forward));
	vec3 newUp = normalize(cross(forward, right));

	float tR = dot(position, right);
	float tU = dot(position, newUp);
	float tF = dot(position, forward);
	
	mat4 view = {
		right.x,   right.y,   right.z,   -tR,
		newUp.x,   newUp.y,   newUp.z,   -tU,
		forward.x, forward.y, forward.z, -tF,
		0.f,       0.f,       0.f,       1.f
	};

	return view;
}

mat4 Camera::getPerspectivematrix()
{
	mat4 mat = mat::identity4(0.f);

	float range = far_ - near_;
	float cotHalfFov = 1.f / tanf(deg2Rad(zoom)/ 2.f);

	mat.e[0] = cotHalfFov / aspect;
	mat.v[1].y = cotHalfFov;
	mat.v[2].z = -(near_ + far_) / range;

	mat.v[2].w = -2.f * near_ * far_ / range;
	mat.v[3].z = -1.f;
	
	return mat;
}

void Camera::updateCameraVectors()
{
	front.x = cos(deg2Rad(yaw)) * cos(deg2Rad(pitch));
	front.y = sin(deg2Rad(pitch));
	front.z = sin(deg2Rad(yaw)) * cos(deg2Rad(pitch));
	front = normalize(front);

	right = normalize(cross(front, worldUp));
	up = normalize(cross(right, front));
}