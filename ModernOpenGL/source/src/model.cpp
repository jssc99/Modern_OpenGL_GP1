#include "../include/model.hpp"

using namespace Resources;

void Model::makeModel(Texture* tex, LowRenderer::Mesh* m)
{
	if (!m)
	{
		DEBUG_LOG("model mesh not loaded, invalid mesh");
		return;
	}
	mesh = m;

	if (addTexture(tex)) return;

	buffer = new Buffer(mesh->vertices, mesh->indices);
	if (!buffer)
	{
		DEBUG_LOG("model buffer not created");
		return;
	}
}

void Model::makeModel(vector<Texture*> texs, LowRenderer::Mesh* m)
{
	if (!mesh)
	{
		DEBUG_LOG("model mesh not loaded, invalid mesh");
		return;
	}
	mesh = m;

	for (Texture* tex : texs)
		if (addTexture(tex)) return;

	buffer = new Buffer(mesh->vertices, mesh->indices);
	if (!buffer)
	{
		DEBUG_LOG("model buffer not created");
		return;
	}
}

int Model::addTexture(Texture* tex)
{
	if (!tex)
	{
		DEBUG_LOG("model texture not loaded, invalid texture");
		return 1;
	}
	textures.push_back(tex);
	return 0;
}

void Model::draw()
{
	glBindVertexArray(buffer->VAO);

	for (Texture* texture : textures)
		texture->use();

	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	for (Texture* texture : textures)
		texture->stopUse();
}