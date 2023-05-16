#ifndef IRESOURCE_H
#define IRESOURCE_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
#include <string>

#include "debug.hpp"

class IResource
{
public:
	IResource();
	~IResource();

	std::string name;

private:
};
#endif