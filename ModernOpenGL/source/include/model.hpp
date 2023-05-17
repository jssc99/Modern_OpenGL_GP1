#ifndef MODEL_H
#define MODEL_H

#include "IResource.hpp"
#include "basicMath.hpp"

#include <vector>
using std::vector;

struct Vertex
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 TextureUV;
};

class Model : public IResource
{
public:
	Model() {};
	~Model() {};

	void loadResource(fs::path filePath) override;

private:
	vector<Vertex> vertices;
	vector<uint32_t> indices;
};
#endif