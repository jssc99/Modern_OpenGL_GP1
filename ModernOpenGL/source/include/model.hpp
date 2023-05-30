#pragma once

#include <vector>
using std::vector;

#include "buffer.hpp"
#include "IResource.hpp"
#include "texture.hpp"
#include "mesh.hpp"

namespace Resources {
	class Model
	{
	public:
		Model() {};
		~Model() {
			delete buffer;
			// texture and mesh should be delete by ResourceManager
		};

		void makeModel(Texture* tex, LowRenderer::Mesh* mesh);
		//void makeModel(vector<Texture*> texs, vector<LowRenderer::Mesh*> meshs);

		void draw(int GL_Tex = 0);

	private:
		Texture* texture = nullptr;
		LowRenderer::Mesh* mesh = nullptr;
		Buffer* buffer = nullptr;

		//vector<Texture*> textures;
		//vector<LowRenderer::Mesh*> meshes;
		//vector<Buffer*> buffers;
	};
}