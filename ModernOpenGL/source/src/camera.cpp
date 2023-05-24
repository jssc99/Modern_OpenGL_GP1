#include "../include/camera.hpp"
#include "../include/debug.hpp"

Camera::Camera(int width, int height)
{
	aspect = (float)width / height;
	updateCameraVectors();
}

Camera::~Camera()
{}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += speed * deltaTime * front;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= speed * deltaTime * front;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= calc::norm(calc::cross(front, up)) * speed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += calc::norm(calc::cross(front, up)) * speed * deltaTime;
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

glm::mat4 Camera::getViewmatrix()
{
	glm::vec3 Position = { position.x, position.y, position.z };
	glm::vec3 Target = { position.x + front.x, position.y + front.y, position.z + front.z };
	glm::vec3 Up = { up.x, up.y, up.z };
	return glm::lookAt(Position, Target, Up);

	//return mat::identity4();
	vec3 forward = calc::norm(-front);
	vec3 right = calc::norm(calc::cross(calc::norm(up), forward));
	vec3 newUp = calc::norm(calc::cross(forward, right));

	float tR = calc::dot(position, right);
	float tU = calc::dot(position, newUp);
	float tF = calc::dot(position, forward);
	
	mat4 view = {
		right.x,   right.y,   right.z,   -tR,
		newUp.x,   newUp.y,   newUp.z,   -tU,
		forward.x, forward.y, forward.z, -tF,
		0.f,       0.f,       0.f,       1.f
	};

	//return view;
}

glm::mat4 Camera::getPerspectivematrix()
{
	return glm::perspective(zoom, aspect, near_, far_);

	//return mat::identity4();
	mat4 mat = mat::identity4(0.f);

	float range = far_ - near_;
	float cotHalfFov = 1.f / tanf(calc::deg2Rad(zoom)/ 2.f);

	mat.e[0] = cotHalfFov / aspect;
	mat.v[1].y = cotHalfFov;
	mat.v[2].z = -(near_ + far_) / range;

	mat.v[2].w = -2.f * near_ * far_ / range;
	mat.v[3].z = -1.f;
	
	//return mat;
}

void Camera::updateCameraVectors()
{
	front.x = cos(calc::deg2Rad(yaw)) * cos(calc::deg2Rad(pitch));
	front.y = sin(calc::deg2Rad(pitch));
	front.z = sin(calc::deg2Rad(yaw)) * cos(calc::deg2Rad(pitch));
	front = calc::norm(front);

	right = calc::norm(calc::cross(front, worldUp));
	up = calc::norm(calc::cross(right, front));
}