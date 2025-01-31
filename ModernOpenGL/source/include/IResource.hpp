#pragma once

#include <glad/glad.h>
#include <string>

#include "debug.hpp"

namespace Resources {
	class IResource
	{
	public:
		virtual void loadResource(fs::path filePath) = 0;

		unsigned int ID = 0;
		fs::path path;
	};
}