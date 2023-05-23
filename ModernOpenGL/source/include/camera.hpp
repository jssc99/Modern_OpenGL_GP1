#ifndef CAMERA_H
#define CAMERA_H

#include "basicMath.hpp"

class Camera
{
public:
	Camera();
	~Camera();

private:
	Vec3 position = { 0.f, 0.f, 3.f };
	Vec3 target = { 0.f,0.f,0.f };
	Vec3 direction;

	Vec3 up = { 0.f,1.f,0.f };
	Vec3 right;
};
#endif