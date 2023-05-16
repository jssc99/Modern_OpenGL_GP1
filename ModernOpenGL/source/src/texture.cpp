#include "../include/texture.hpp"
#include "../include/debug.hpp"

Texture::Texture(std::string texturePath, std::string name)
{
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		if (nrChannels == 3)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		else if (nrChannels == 4)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		else
			DEBUG_LOG("Failed to load texture because of nrChannels: " << texturePath);

		glGenerateMipmap(GL_TEXTURE_2D);

		this->name = name;
	}
	else
		DEBUG_LOG("Failed to load texture because of wrong filePath: " << texturePath);

	stbi_image_free(data);
}

Texture::~Texture()
{
}

void Texture::use(int GL_textureSlot)
{
	glActiveTexture(GL_textureSlot);
	glBindTexture(GL_TEXTURE_2D, ID);
}
