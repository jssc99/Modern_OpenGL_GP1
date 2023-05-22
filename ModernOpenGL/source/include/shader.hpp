#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include "debug.hpp"
#include "IResource.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader : public IResource
{
public:
    Shader() {};
    ~Shader();

    void loadResource(fs::path shaderName) override;

    bool setVertexS(fs::path filePath, bool autoLink = false);
    bool setFragmentS(fs::path filePath, bool autoLink = false);
    bool linkShaders();

    void use();

    void setBool(const string& name, bool value) const;
    void setInt(const string& name, int value) const;
    void setFloat(const string& name, float value) const;

private:
    unsigned int vertex = 0, fragment = 0;

    bool checkCompileErrors(unsigned int shader, string type);
};

#endif