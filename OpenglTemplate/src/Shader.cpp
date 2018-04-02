#include "Shader.h"
#include "Renderer.h"
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const std::string & filepath):
	m_FilePath(filepath), m_RendererID(0)
{
	ShadersSourcePrograms parsedShaders = ParseShaders();

	m_RendererID = CreateShader(parsedShaders.vertexShaderSource, parsedShaders.fragmentShaderSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

ShadersSourcePrograms Shader::ParseShaders()
{
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::ifstream stream(m_FilePath);
	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (std::getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
				type = ShaderType::VERTEX;
			else if (line.find("fragment") != std::string::npos)
				type = ShaderType::FRAGMENT;

		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}
	return{ ss[0].str(),ss[1].str() };
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const GLchar * src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	GLint resualt;
	glGetShaderiv(id, GL_COMPILE_STATUS, &resualt);
	if (resualt == GL_FALSE)
	{
		GLint length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char * message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Error in compiling " << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment") << " Shader!\n" << message << '\n';
		glDeleteShader(id);
		return 0;
	}
	return id;
}



unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}
void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}
int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
		return m_UniformLocationCache[name];

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: Uniform '" << name << "' doesn't exist!\n";

	m_UniformLocationCache[name] = location;
	return location;
}


void Shader::SetUniform4f(const std::string & name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}
void Shader::SetUniformMat4f(const std::string & name,glm::mat4& mat)
{
GLCall(glUniformMatrix4fv(GetUniformLocation(name),1,0,&mat[0][0]));
}




