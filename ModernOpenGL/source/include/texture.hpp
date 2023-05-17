#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <stb_image.h>
#include <iostream>

#include "IResource.hpp"

class Texture : public IResource
{
public:
    Texture();
    ~Texture();

    void use(int GL_textureSlot);

    void loadResource(fs::path filePath) override;

private:
    int width = 0, height = 0, nrChannels = 0;
};

#endif