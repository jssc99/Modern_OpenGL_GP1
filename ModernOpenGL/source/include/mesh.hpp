#pragma once

#include "IResource.hpp"
#include "basicMath.hpp"
#include "buffer.hpp"

#include <vector>
using std::vector;

namespace LowRenderer {
	class Mesh : public Resources::IResource
	{
	public:
		Mesh() {};
		~Mesh() {};

		void loadResource(fs::path filePath) override;

		vector<Resources::Vertex> vertices;
		vector<uint32_t> indices;

	private:
		vector<vec3> tmpVPos;
		vector<vec3> tmpVNorm;
		vector<vec2> tmpVText;

		uint32_t getIndice(string& line);

		uint32_t getPosString(string line);
		uint32_t getNorString(string line);
		uint32_t getTexString(string line);
	};
}