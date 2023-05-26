#pragma once

#include <vector>
using std::vector;

#include "buffer.hpp"
#include "IResource.hpp"

namespace Resources {
	class Model : public IResource
	{
	public:
		Model() {};
		~Model() {
			delete buffer;
		};

		void loadResource(fs::path filePath) override;

		void draw();

	private:
		vector<Vertex> vertices;
		vector<uint32_t> indices;

		vector<vec3> tmpVPos;
		vector<vec3> tmpVNorm;
		vector<vec2> tmpVText;

		uint32_t getIndice(string& line);

		uint32_t getPosString(string line);
		uint32_t getNorString(string line);
		uint32_t getTexString(string line);

		Buffer* buffer = nullptr;
	};
}