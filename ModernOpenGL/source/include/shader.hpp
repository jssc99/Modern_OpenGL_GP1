#pragma once

#include <glad/glad.h>

#include "debug.hpp"
#include "IResource.hpp"
#include "basicmath.hpp"
#include "light.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

namespace Resources {
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
		void stopUse();

		void setBool(const string& name, bool value) const;
		void setInt(const string& name, int value) const;
		void setFloat(const string& name, float value) const;
		void setVec2(const std::string& name, const vec2& value) const;
		void setVec2(const std::string& name, float x, float y) const;
		void setVec3(const std::string& name, const vec3& value) const;
		void setVec3(const std::string& name, float x, float y, float z) const;
		void setVec4(const std::string& name, const mat4& value) const;
		void setVec4(const std::string& name, float x, float y, float z, float w) const;
		void setMat3(const std::string& name, const mat3& mat) const;
		void setMat4(const std::string& name, const mat4& mat) const;

		void setDirLight(const LowRenderer::DirLight& light, const unsigned int& idLight) const;
		void setPointLight(const LowRenderer::PointLight& light, const unsigned int& idLight) const;
		void setSpotLight(const LowRenderer::SpotLight& light, const unsigned int& idLight) const;

	private:
		unsigned int vertex = 0, fragment = 0;

		void setBaseLight(const string& name, const LowRenderer::BaseLight& light) const;
		bool checkCompileErrors(unsigned int& shader, string type);
	};
}