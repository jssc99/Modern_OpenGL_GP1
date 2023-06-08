#include "../include/shader.hpp"
#include "../include/debug.hpp"

using namespace Resources;

Shader::~Shader() {
	glDeleteProgram(ID);
}

void Shader::loadResource(fs::path shaderName)
{
	DEBUG_LOG("loading: %s", shaderName.string().c_str());
	fs::path vertexPath, fragmentPath;
	if (shaderName.extension() == ".frag")
	{
		fragmentPath = shaderName;
		vertexPath = shaderName.replace_extension(".vert");
	}
	else if (shaderName.extension() == ".vert")
	{
		vertexPath = shaderName;
		fragmentPath = shaderName.replace_extension(".frag");
	}
	else
		DEBUG_LOG("No proper extension found, Shader class uses .vert & .frag");

	setVertexS(vertexPath);
	setFragmentS(fragmentPath, true);

	setInt("nbDirLight", 0);
	setInt("nbPointLight", 0);
	setInt("nbSpotLight", 0);
}

string loadCode(fs::path path)
{
	string code; std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		shaderFile.open(path.string());

		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();

		shaderFile.close();
		code = shaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		DEBUG_LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: ", e.what());
	}
	return code;
}

// returns 1 on error
bool Shader::setVertexS(fs::path filePath, bool autoLink)
{
	string code = loadCode(filePath);
	const char* ShaderCode = code.c_str();

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &ShaderCode, NULL);
	glCompileShader(vertex);
	bool success = checkCompileErrors(vertex, "VERTEX");

	if (success) return success;

	if (!success && autoLink)
		return linkShaders();

	return success;
}

// returns 1 on error
bool Shader::setFragmentS(fs::path filePath, bool autoLink)
{
	string code = loadCode(filePath);
	const char* ShaderCode = code.c_str();

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &ShaderCode, NULL);
	glCompileShader(fragment);
	bool success = checkCompileErrors(fragment, "FRAGMENT");

	if (success) return success;

	if (!success && autoLink)
		return linkShaders();

	return success;
}

// returns 1 on error
bool Shader::linkShaders()
{
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return checkCompileErrors(ID, "LINKING");
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::stopUse() {
	glUseProgram(0);
}

void Shader::setBool(const string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec2(const std::string& name, const vec2& value) const {
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, value.e);
}

void Shader::setVec2(const std::string& name, float x, float y) const {
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const vec3& value) const {
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, value.e);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const {
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const mat4& value) const {
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, value.e);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const {
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void Shader::setMat3(const std::string& name, const mat3& mat) const {
	mat3 fliped = {
			   mat.v[0].x, mat.v[1].x, mat.v[2].x,
			   mat.v[0].y, mat.v[1].y, mat.v[2].y,
			   mat.v[0].z, mat.v[1].z, mat.v[2].z,
	};
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, fliped.e);
}

void Shader::setMat4(const std::string& name, const mat4& mat) const {
	mat4 fliped = {
			   mat.v[0].x, mat.v[1].x, mat.v[2].x, mat.v[3].x,
			   mat.v[0].y, mat.v[1].y, mat.v[2].y, mat.v[3].y,
			   mat.v[0].z, mat.v[1].z, mat.v[2].z, mat.v[3].z,
			   mat.v[0].w, mat.v[1].w, mat.v[2].w, mat.v[3].w
	};
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, fliped.e);
}

void Shader::setBaseLight(const string& name, const LowRenderer::BaseLight& light) const
{
	this->setVec3(name + string("ambient"), light.ambient);
	this->setVec3(name + string("diffuse"), light.diffuse);
	this->setVec3(name + string("specular"), light.specular);
}

// idLight starts at 0, ends at 9 (per light type, total 30 lights possible)
void Shader::setDirLight(const LowRenderer::DirLight& light, const unsigned int& idLight) const
{
	string name("dirLights[" + idLight + string("]."));
	this->setVec3(name + string("direction"), light.direction);
	this->setBaseLight(name, light.base);
}

// idLight starts at 0, ends at 9 (per light type, total 30 lights possible)
void Shader::setPointLight(const LowRenderer::PointLight& light, const unsigned int& idLight) const
{
	string name("pointLights[" + idLight + string("]."));
	this->setVec3(name + string("position"), light.position);

	this->setBaseLight(name, light.base);

	this->setFloat(name + string("constant"), light.constant);
	this->setFloat(name + string("linear"), light.linear);
	this->setFloat(name + string("quadratic"), light.quadratic);
}

// idLight starts at 0, ends at 9 (per light type, total 30 lights possible)
void Shader::setSpotLight(const LowRenderer::SpotLight& light, const unsigned int& idLight) const
{
	string name("spotLights[" + idLight + string("]."));
	this->setVec3(name + string("position"), light.position);
	this->setVec3(name + string("direction"), light.direction);

	this->setBaseLight(name, light.base);

	this->setFloat(name + string("constant"), light.constant);
	this->setFloat(name + string("linear"), light.linear);
	this->setFloat(name + string("quadratic"), light.quadratic);

	this->setFloat(name + string("cutOff"), light.cutOff);
	this->setFloat(name + string("outerCutOff"), light.outerCutOff);
}

// returns 1 on error
bool Shader::checkCompileErrors(unsigned int& shader, string type)
{
	int success; char infoLog[1024];
	if (type != "LINKING")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			DEBUG_LOG("ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s \n-------------------------------------------------------"
				, type.c_str(), infoLog);
			return 1;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			DEBUG_LOG("ERROR::PROGRAM_LINKING_ERROR of type: %s \n %s \n-------------------------------------------------------"
				, type.c_str(), infoLog);
			return 1;
		}
	}
	return 0;
}