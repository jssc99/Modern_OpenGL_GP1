#ifndef MODEL_H
#define MODEL_H

class Buffer;

#include <vector>
using std::vector;

#include "basicMath.hpp"
struct Vertex
{
	Vec3 Position;
	Vec3 Normal;
	Vec2 TextureUV;
};

#include "IResource.hpp"
#include "buffer.hpp"

class Model : public IResource
{
public:
	Model() {
		loadFromPath();
	};
	~Model();

	void loadResource(fs::path filePath) override;

	void draw();

private:
	vector<Vertex> vertices;
	vector<uint32_t> indices;

	vector<Vec3> tmpVPos;
	vector<Vec2> tmpVText;
	vector<Vec3> tmpVNorm;

	uint32_t createIndice(string& line);

	uint32_t getPosString(string line);
	uint32_t getTexString(string line);
	uint32_t getNorString(string line);

	Buffer* buffer = nullptr;
};
#endif