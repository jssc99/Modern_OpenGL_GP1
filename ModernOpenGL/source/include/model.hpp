#pragma once

#include <vector>
using std::vector;

#include "buffer.hpp"
#include "IResource.hpp"
#include "texture.hpp"
#include "mesh.hpp"
#include "shader.hpp"

namespace Resources {
	class Model
	{
	public:
		Model() {};
		~Model() {
			delete buffer;
			// texture and mesh should be delete by ResourceManager
		};

		void makeModel(Texture* tex, LowRenderer::Mesh* m, Shader* shad);
		void makeModel(vector<Texture*> texs, LowRenderer::Mesh* m, Shader* shad);

		int addTexture(Texture* tex);

		void draw();

		vector<Texture*> textures;
		LowRenderer::Mesh* mesh = nullptr;
		Buffer* buffer = nullptr;
		Shader* shader = nullptr;
	};
}