#pragma once

#include "types.hpp"

namespace Core::Maths
{
	namespace vec
	{
		inline vec4 one4(float val = 1.f) {
			return { val, val, val, val };
		}

		inline vec3 one3(float val = 1.f) {
			return { val, val, val };
		}
	}

	namespace mat
	{
		inline mat4 identity4(float val = 1.f)
		{
			return {
				val, 0.f, 0.f, 0.f,
				0.f, val, 0.f, 0.f,
				0.f, 0.f, val, 0.f,
				0.f, 0.f, 0.f, val,
			};
		}
		mat4 translate(float x, float y, float z);
		mat4 translate(vec3 v);
		mat4 scale(float x, float y, float z);
		mat4 scale(vec3 v);
		mat4 rotateX(float angleDeg);
		mat4 rotateY(float angleDeg);
		mat4 rotateZ(float angleDeg);
		mat4 rotate(float angleDeg, vec3 axis);

		inline mat3 identity3(float val = 1.f)
		{
			return {
				val, 0.f, 0.f,
				0.f, val, 0.f,
				0.f, 0.f, val,
			};
		}
	}

	const float TAU = 6.28318530717f;
	const float PI = TAU / 2.f;

	inline float deg2Rad(float Deg) {
		return Deg * TAU / 360.f;
	};

	inline float rad2Deg(float Rad) {
		return Rad * 360.f / TAU;
	};

	inline float length(vec3 v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}

	inline vec3 normalize(vec3 v) {
		float l = length(v);
		if (l > .00001f)
			return v / l;
		return { 0.0f, 0.0f, 0.0f };
	}

	inline vec3 cross(vec3 a, vec3 b) {
		return { a.y * b.z - a.z * b.y,
					a.z * b.x - a.x * b.z,
					a.x * b.y - a.y * b.x };
	}

	inline float dot(vec3 a, vec3 b) {
		return a.x * b.x + a.y * b.y + a.z * b.z;
	}

	template <class T> inline T max_(T a, T b) {
		return (a > b) ? a : b;
	}

	template <class T> inline T min_(T a, T b) {
		return (a < b) ? a : b;
	}

	inline float edge(vec3 a, vec3 b, vec3 c) {
		return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
	}
}