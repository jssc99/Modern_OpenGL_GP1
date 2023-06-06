#pragma once

#include <glad/glad.h>

#include <stb_image.h>
#include <iostream>

#include "IResource.hpp"

namespace Resources {
	class Texture : public IResource
	{
	public:
		Texture() {};
		~Texture() {};

		void loadResource(fs::path filePath) override;

		void use();
		void stopUse();

	private:
		int width = 0, height = 0, nrChannels = 0;
	};
}