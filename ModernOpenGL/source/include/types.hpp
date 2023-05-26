#pragma once

#include <cmath>
#include <ostream>

union vec2
{
	float e[2];
	struct { float x, y; };
	struct { float u, v; };
};

union vec3
{
	vec3() = default;
	vec3(float x, float y, float z) :
		x(x), y(y), z(z) {};
	vec3(vec2 v, float z) : x(v.x), y(v.y), z(z) {};

	float e[3];
	struct { float x, y, z; };

	vec2 xy;
};

union vec4
{
	vec4() = default;
	vec4(vec3 v, float w) :
		x(v.x), y(v.y), z(v.z), w(w) {};
	vec4(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w) {};

	float e[4];
	struct { float x, y, z, w; };
	struct { float r, g, b, a; };

	vec3 xyz;
};

union mat3
{
	float e[9];
	vec3 v[3];
};

union mat4
{
	float e[16];
	vec4 v[4];
};

// All Operators
#pragma region vecOperator
inline bool operator==(const vec2& u, const vec2& v) {
	return (u.x == v.x && u.y == v.y);
}

inline bool operator==(const vec3& u, const vec3& v) {
	return (u.x == v.x && u.y == v.y && u.z == v.z);
}

inline bool operator==(const vec4& u, const vec4& v) {
	return (u.x == v.x && u.y == v.y && u.z == v.z && u.w == v.w);
}

inline bool operator!=(const vec2& u, const vec2& v) {
	return !(u == v);
}

inline bool operator!=(const vec3& u, const vec3& v) {
	return !(u == v);
}

inline bool operator!=(const vec4& u, const vec4& v) {
	return !(u == v);
}

inline vec3 operator+(const vec3& v, const vec3& u) {
	return { v.x + u.x,v.y + u.y,v.z + u.z };
}

inline vec4 operator+(const vec4& v, const vec4& u) {
	return { v.x + u.x,v.y + u.y,v.z + u.z,v.w + u.w };
}

inline vec3 operator-(const vec3& v, const vec3& u) {
	return { v.x - u.x,v.y - u.y,v.z - u.z };
}

inline vec4 operator-(const vec4& v, const vec4& u) {
	return { v.x - u.x,v.y - u.y,v.z - u.z,v.w - u.w };
}

//inline vec3 operator+(const vec3& v) {
//	return { abs(v.x),abs(v.y),abs(v.z) };
//}

inline vec3 operator-(const vec3& v) {
	return { -v.x,-v.y,-v.z };
}

//inline vec4 operator+(const vec4& v) {
//	return { abs(v.x),abs(v.y),abs(v.z),abs(v.w)};
//}

inline vec4 operator-(const vec4& v) {
	return { -v.x,-v.y,-v.z,-v.w };
}

inline vec3 operator+=(vec3& v, const vec3& a) {
	return v = v + a;
}

inline vec4 operator+=(vec4& v, const vec4& a) {
	return v = v + a;
}

inline vec3 operator-=(vec3& v, const vec3& a) {
	return v = v - a;
}

inline vec4 operator-=(vec4& v, const vec4& a) {
	return v = v - a;
}

inline vec3 operator*(const vec3& v, const float& a) {
	return { v.x * a,v.y * a,v.z * a };
}

inline vec4 operator*(const vec4& v, const float& a) {
	return { v.x * a,v.y * a,v.z * a,v.w * a };
}

inline vec3 operator/(const vec3& v, const float& a) {
	return { v.x / a,v.y / a,v.z / a };
}

inline vec4 operator/(const vec4& v, const float& a) {
	return { v.x / a,v.y / a,v.z / a,v.w / a };
}

inline vec3 operator*(const float& v, const vec3& a) {
	return a * v;
}

inline vec4 operator*(const float& v, const vec4& a) {
	return a * v;
}

inline vec3 operator/(const float& v, const vec3& a) {
	return a / v;
}

inline vec4 operator/(const float& v, const vec4& a) {
	return a / v;
}

// NOT A DOT PRODUCT: use Calc::dot
inline vec3 operator*(const vec3& m, const vec3& v) {
	return { m.x * v.x , m.y * v.y , m.z * v.z };
}

// NOT A DOT PRODUCT: use Calc::dot
inline vec4 operator*(const vec4& m, const vec4& v) {
	return { m.x * v.x , m.y * v.y , m.z * v.z , m.w * v.w };
}

inline vec3 operator/(const vec3& m, const vec3& v) {
	return { m.x / v.x , m.y / v.y , m.z / v.z };
}

inline vec4 operator/(const vec4& m, const vec4& v) {
	return { m.x / v.x , m.y / v.y , m.z / v.z , m.w / v.w };
}

inline vec3 operator*=(vec3& v, const vec3& a) {
	return v = v * a;
}

inline vec4 operator*=(vec4& v, const vec4& a) {
	return v = v * a;
}

inline vec3 operator/=(vec3& v, const vec3& a) {
	return v = v / a;
}

inline vec4 operator/=(vec4& v, const vec4& a) {
	return v = v / a;
}
#pragma endregion
#pragma region matOperator
inline mat3 operator*(const mat3& a, const mat3& b)
{
	mat3 r = {
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f,
			0.f, 0.f, 0.f,
	};

	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			for (int k = 0; k < 3; k++)
				r.e[row * 3 + col] += a.e[row * 3 + k] * b.e[k * 3 + col];

	return r;
}

inline mat4 operator*(const mat4& a, const mat4& b)
{
	mat4 r = {
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
			0.f, 0.f, 0.f, 0.f,
	};

	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			for (int k = 0; k < 4; k++)
				r.e[row * 4 + col] += a.e[row * 4 + k] * b.e[k * 4 + col];

	return r;
}

inline mat3 operator*=(mat3& a, const mat3& b)
{
	return a = a * b;
}

inline mat4 operator*=(mat4& a, const mat4& b)
{
	return a = a * b;
}

inline mat3 operator*(const float& a, const mat3& b)
{
	mat3 r = b;

	for (int all = 0; all < 3 * 3; all++)
		r.e[all] *= a;

	return r;
}

inline mat4 operator*(const float& a, const mat4& b)
{
	mat4 r = b;

	for (int all = 0; all < 4 * 4; all++)
		r.e[all] *= a;

	return r;
}

inline mat3 operator+(const mat3& a, const mat3& b)
{
	mat3 r;

	for (int all = 0; all < 3 * 3; all++)
		r.e[all] = a.e[all] + b.e[all];

	return r;
}

inline mat4 operator+(const mat4& a, const mat4& b)
{
	mat4 r;

	for (int all = 0; all < 4 * 4; all++)
		r.e[all] = a.e[all] + b.e[all];

	return r;
}

inline vec3 operator*(const mat3& m, const vec3& v)
{
	vec3 r = { 0.f,0.f,0.f };

	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			r.e[row] += v.e[col] * m.e[row * 3 + col];

	return r;
}

inline vec4 operator*(const mat4& m, const vec4& v)
{
	vec4 r = { 0.f, 0.f, 0.f, 0.f };

	for (int row = 0; row < 4; row++)
		for (int col = 0; col < 4; col++)
			r.e[row] += v.e[col] * m.e[row * 4 + col];

	return r;
}
#pragma endregion
#pragma region stdOutput
inline std::ostream& operator<<(std::ostream& os, const mat4& mat)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			os << mat.e[i * 4 + j] << " | ";
		os << '\n';
	}
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const mat3& mat)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++)
			os << mat.e[i * 3 + j] << " | ";
		os << '\n';
	}
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const vec3& mat)
{
	for (int i = 0; i < 3; i++)
		os << mat.e[i] << " | ";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const vec4& mat)
{
	for (int i = 0; i < 4; i++)
		os << mat.e[i] << " | ";
	return os;
}

inline std::ostream& operator<<(std::ostream& os, const vec2& mat)
{
	for (int i = 0; i < 2; i++)
		os << mat.e[i] << " | ";
	return os;
}
#pragma endregion