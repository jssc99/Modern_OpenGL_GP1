#include "../include/shader.hpp"
#include "../include/debug.hpp"

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::loadResource(fs::path shaderName)
{
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
}

string loadCode(fs::path path)
{
	string code; std::ifstream ShaderFile;
	ShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		ShaderFile.open(path.string());

		std::stringstream ShaderStream;
		ShaderStream << ShaderFile.rdbuf();

		ShaderFile.close();
		code = ShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		DEBUG_LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
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

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

// returns 1 on error
bool Shader::checkCompileErrors(unsigned int shader, string type)
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