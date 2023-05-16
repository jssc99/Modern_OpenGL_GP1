#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <stb_image.h>
#include <iostream>

#include "IResource.hpp"

class Texture : IResource
{
public:
    Texture(std::string texturePath, std::string name);
    ~Texture();

    unsigned int ID;

    // use/activate the texture
    void use(int GL_textureSlot);

private:
    int width, height, nrChannels;
};

#endif