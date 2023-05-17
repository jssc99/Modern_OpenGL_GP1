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
    unsigned int ID;

    Shader() {};
    ~Shader();

    void loadResource(fs::path shaderName) override;

    void use();

    void setBool(const string& name, bool value) const;
    void setInt(const string& name, int value) const;
    void setFloat(const string& name, float value) const;

private:
    void checkCompileErrors(unsigned int shader, string type);
};

#endif