#pragma once

#include <glad/glad.h> // include glad to get all the required OpenGL headers

#include <vector>
using std::vector;

#include "model.hpp"

class Buffer
{
public:
	Buffer(vector<Vertex>& vertices, vector<uint32_t>& indices);
	~Buffer();

	unsigned int VAO, VBO, EBO;
};