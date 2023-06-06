#include "../include/model.hpp"

using namespace Resources;

void Model::makeModel(Texture* tex, LowRenderer::Mesh* m, Shader* shad)
{
	if (!m)
	{
		DEBUG_LOG("model mesh not loaded, invalid mesh");
		return;
	}
	mesh = m;

	if (!shad)
	{
		DEBUG_LOG("model shader not loaded, invalid shader");
		return;
	}
	shader = shad;

	if (addTexture(tex)) return;

	buffer = new Buffer(mesh->vertices, mesh->indices);
	if (!buffer)
	{
		DEBUG_LOG("model buffer not created");
		return;
	}
}

void Model::makeModel(vector<Texture*> texs, LowRenderer::Mesh* m, Shader* shad)
{
	if (!mesh)
	{
		DEBUG_LOG("model mesh not loaded, invalid mesh");
		return;
	}
	mesh = m;

	if (!shad)
	{
		DEBUG_LOG("model shader not loaded, invalid shader");
		return;
	}
	shader = shad;

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

	shader->use();

	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	shader->stopUse();

	for (Texture* texture : textures)
		texture->stopUse();
}