#include "Shader.h"
#include <GL\glew.h>
#include "GLErrorHandler.h"
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


void Shader::SetUniformElement(const std::string & name, float v0)
{
	GLCall(glUniform1f(GetUniformLocation(name), v0));
}

void Shader::SetUniformElement(const std::string & name, float v0,float v1)
{
	GLCall(glUniform2f(GetUniformLocation(name), v0,v1));
}

void Shader::SetUniformElement(const std::string & name, float v0, float v1,float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1,v2));
}

void Shader::SetUniformElement(const std::string & name, float v0, float v1, float v2,float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2,v3));
}


void Shader::SetUniformElement(const std::string & name, unsigned int v0)
{
	GLCall(glUniform1ui(GetUniformLocation(name), v0));
}

void Shader::SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1)
{
	GLCall(glUniform2ui(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1, unsigned int v2)
{
	GLCall(glUniform3ui(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3)
{
	GLCall(glUniform4ui(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformElement(const std::string & name, int v0)
{
	GLCall(glUniform1i(GetUniformLocation(name), v0));
}

void Shader::SetUniformElement(const std::string & name, int v0, int v1)
{
	GLCall(glUniform2i(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniformElement(const std::string & name, int v0, int v1, int v2)
{
	GLCall(glUniform3i(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformElement(const std::string & name, int v0, int v1, int v2, int v3)
{
	GLCall(glUniform4i(GetUniformLocation(name), v0, v1, v2, v3));
	
}

void Shader::SetUniformElement(const std::string & name, double v0)
{
	GLCall(glUniform1d(GetUniformLocation(name), v0));
}

void Shader::SetUniformElement(const std::string & name, double v0, double v1)
{
	GLCall(glUniform2d(GetUniformLocation(name), v0, v1));
}

void Shader::SetUniformElement(const std::string & name, double v0, double v1, double v2)
{
	GLCall(glUniform3d(GetUniformLocation(name), v0, v1, v2));
}

void Shader::SetUniformElement(const std::string & name, double v0, double v1, double v2, double v3)
{
	GLCall(glUniform4d(GetUniformLocation(name), v0, v1, v2, v3));

}



void Shader::SetUniformElement(const std::string & name, glm::mat2& mat)
{
	GLCall(glUniformMatrix2fv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}

void Shader::SetUniformElement(const std::string & name, glm::mat3& mat)
{
	GLCall(glUniformMatrix3fv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}

void Shader::SetUniformElement(const std::string & name, glm::mat4& mat)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}

void Shader::SetUniformElement(const std::string & name, glm::dmat2 mat)
{
	GLCall(glUniformMatrix2dv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}

void Shader::SetUniformElement(const std::string & name, glm::dmat3 mat)
{
	GLCall(glUniformMatrix3dv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}


void Shader::SetUniformElement(const std::string & name, glm::dmat4 mat)
{
	GLCall(glUniformMatrix4dv(GetUniformLocation(name), 1, 0, &mat[0][0]));
}


void Shader::SetUniformElement(const std::string& name, glm::vec2 vec) 
{
	GLCall(glUniform2fv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::vec3 vec)
{
	GLCall(glUniform3fv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::vec4 vec)
{
	GLCall(glUniform4fv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::ivec2 vec)
{
	GLCall(glUniform2iv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::ivec3 vec)
{
	GLCall(glUniform3iv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::ivec4 vec)
{
	GLCall(glUniform4iv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::dvec2 vec)
{
	GLCall(glUniform2dv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::dvec3 vec)
{
	GLCall(glUniform3dv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::dvec4 vec)
{
	GLCall(glUniform4dv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::uvec2 vec)
{
	GLCall(glUniform2uiv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::uvec3 vec)
{
	GLCall(glUniform3uiv(GetUniformLocation(name), 1, &vec[0]));
}

void Shader::SetUniformElement(const std::string& name, glm::uvec4 vec)
{
	GLCall(glUniform4uiv(GetUniformLocation(name), 1, &vec[0]));
}