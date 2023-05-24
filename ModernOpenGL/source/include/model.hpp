#pragma once

class Buffer;

#include <vector>
using std::vector;

#include "basicmath.hpp"
struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TextureUV;
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

	vector<vec3> tmpVPos;
	vector<vec2> tmpVText;
	vector<vec3> tmpVNorm;

	uint32_t createIndice(string& line);

	uint32_t getPosString(string line);
	uint32_t getTexString(string line);
	uint32_t getNorString(string line);

	Buffer* buffer = nullptr;
};