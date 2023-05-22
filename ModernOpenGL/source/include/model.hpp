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

	uint32_t createIndice(string line, vector<Vec3>& tmpVPos, vector<Vec2>& tmpVText, vector<Vec3>& tmpVNorm);

	uint32_t getPosString(string line);
	uint32_t getTexString(string line);
	uint32_t getNorString(string line);
};
#endif