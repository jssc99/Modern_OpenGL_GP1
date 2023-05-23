struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

struct Mat3
{
	Vec3 v[3];
};

struct Mat4
{
	Vec4 v[4];
};

static bool operator==(Vec2& u, Vec2& v) {
	if (u.x == v.x && u.y == v.y)
		return true;
	return false;
}

static bool operator==(Vec3& u, Vec3& v) {
	if (u.x == v.x && u.y == v.y && u.z == v.z)
		return true;
	return false;
}