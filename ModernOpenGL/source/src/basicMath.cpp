#include "../include/basicmath.hpp"

using namespace Core;
using namespace Core::Maths;

mat4 mat::translate(float x, float y, float z)
{
	mat4 mat = identity4();

	mat.v[0].w = x;
	mat.v[1].w = y;
	mat.v[2].w = z;

	return mat;
}

mat4 mat::translate(vec3 v)
{
	return translate(v.x, v.y, v.z);
}

mat4 mat::scale(float x, float y, float z)
{
	mat4 mat = identity4();

	mat.v[0].x = x;
	mat.v[1].y = y;
	mat.v[2].z = z;

	return mat;
}

mat4 mat::scale(vec3 v)
{
	return scale(v.x, v.y, v.z);
}

mat4 mat::rotateX(float angleDeg)
{
	mat4 mat = identity4();

	float angleRad = deg2Rad(angleDeg);
	float c = cosf(angleRad), s = sinf(angleRad);

	mat.v[1].y = c;
	mat.v[1].z = -s;
	mat.v[2].y = s;
	mat.v[2].z = c;

	return mat;
}

mat4 mat::rotateY(float angleDeg)
{
	mat4 mat = identity4();

	float angleRad = deg2Rad(angleDeg);
	float c = cosf(angleRad), s = sinf(angleRad);

	mat.v[0].x = c;
	mat.v[0].z = s;
	mat.v[2].x = -s;
	mat.v[2].z = c;

	return mat;
}

mat4 mat::rotateZ(float angleDeg)
{
	mat4 mat = identity4();

	float angleRad = deg2Rad(angleDeg);
	float c = cosf(angleRad), s = sinf(angleRad);

	mat.v[0].x = c;
	mat.v[0].y = -s;
	mat.v[1].x = s;
	mat.v[1].y = c;

	return mat;
}

mat4 mat::rotate(float angleDeg, vec3 v)
{
	float a = deg2Rad(angleDeg);
	float c = cos(a), s = sin(a);

	vec3 axis(normalize(v));
	vec3 cosAx((1.f - c) * axis);

	mat4 mat = mat::identity4();
	mat.v[0].x = c + cosAx.x * axis.x;
	mat.v[1].x = cosAx.x * axis.y + s * axis.z;
	mat.v[2].x = cosAx.x * axis.z - s * axis.y;

	mat.v[0].y = cosAx.y * axis.x - s * axis.z;
	mat.v[1].y = c + cosAx.y * axis.y;
	mat.v[2].y = cosAx.y * axis.z + s * axis.x;

	mat.v[0].z = cosAx.z * axis.x + s * axis.y;
	mat.v[1].z = cosAx.z * axis.y - s * axis.x;
	mat.v[2].z = c + cosAx.z * axis.z;

	return mat;
}