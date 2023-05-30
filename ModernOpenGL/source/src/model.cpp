#include "../include/model.hpp"

using namespace Resources;

void Model::makeModel(Texture* tex, LowRenderer::Mesh* m)
{
	mesh = m;
	if (!mesh)
	{
		DEBUG_LOG("model mesh not loaded, invalid mesh");
		return;
	}
	texture = tex;
	if (!texture)
	{
		DEBUG_LOG("model texture not loaded, invalid texture");
		return;
	}
	buffer = new Buffer(mesh->vertices, mesh->indices);
	if (!buffer)
	{
		DEBUG_LOG("model buffer not created");
		return;
	}
}

void Model::draw(int GL_Tex)
{
	glBindVertexArray(buffer->VAO);
	texture->use(GL_Tex);
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	//for (unsigned int i = 0; i < buffers.size(); i++) {
	//	glBindVertexArray(buffers[i]->VAO);
	//	textures[i]->use(GL_TEXTURE + i);
	//	glDrawElements(GL_TRIANGLES, (GLsizei)meshes[i]->indices.size(), GL_UNSIGNED_INT, 0);
	//	glBindVertexArray(0);
	//}
}