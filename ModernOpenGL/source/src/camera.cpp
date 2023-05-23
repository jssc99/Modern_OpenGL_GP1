#include "../include/camera.hpp"

Camera::Camera()
{
	//direction = normalized(position - target);
	//right = normalize(cross(up, direction));
	//up = cross(direction, right);
}

Camera::~Camera()
{
}
