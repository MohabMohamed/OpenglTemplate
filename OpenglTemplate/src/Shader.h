#pragma once
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <unordered_map>






struct ShadersSourcePrograms
{
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
};


class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	//caching uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:

	Shader(const std::string&);

	~Shader();

	void Bind() const;

	void Unbind() const;
	
	void SetUniformElement(const std::string & name, float v0);

	void SetUniformElement(const std::string & name, float v0, float v1);

	void SetUniformElement(const std::string & name, float v0, float v1, float v2);

	void SetUniformElement(const std::string & name, float v0, float v1, float v2, float v3);

	void SetUniformElement(const std::string & name, unsigned int v0);

	void SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1);

	void SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1, unsigned int v2);

	void SetUniformElement(const std::string & name, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);

	void SetUniformElement(const std::string & name, int v0);

	void SetUniformElement(const std::string & name, int v0, int v1);

	void SetUniformElement(const std::string & name, int v0, int v1, int v2);

	void SetUniformElement(const std::string & name, int v0, int v1, int v2, int v3);

	void SetUniformElement(const std::string & name, double v0);

	void SetUniformElement(const std::string & name, double v0, double v1);

	void SetUniformElement(const std::string & name, double v0, double v1, double v2);

	void SetUniformElement(const std::string & name, double v0, double v1, double v2, double v3);

	void SetUniformElement(const std::string & name, glm::mat2 & mat);

	void SetUniformElement(const std::string & name, glm::mat3 & mat);

	void SetUniformElement(const std::string & name, glm::mat4 & mat);

	void SetUniformElement(const std::string & name, glm::dmat2 mat);

	void SetUniformElement(const std::string & name, glm::dmat3 mat);

	void SetUniformElement(const std::string & name, glm::dmat4 mat);

	void SetUniformElement(const std::string & name, glm::vec2 vec);

	void SetUniformElement(const std::string & name, glm::vec3 vec);

	void SetUniformElement(const std::string & name, glm::vec4 vec);

	void SetUniformElement(const std::string & name, glm::ivec2 vec);

	void SetUniformElement(const std::string & name, glm::ivec3 vec);

	void SetUniformElement(const std::string & name, glm::ivec4 vec);

	void SetUniformElement(const std::string & name, glm::dvec2 vec);

	void SetUniformElement(const std::string & name, glm::dvec3 vec);

	void SetUniformElement(const std::string & name, glm::dvec4 vec);

	void SetUniformElement(const std::string & name, glm::uvec2 vec);

	void SetUniformElement(const std::string & name, glm::uvec3 vec);

	void SetUniformElement(const std::string & name, glm::uvec4 vec);
	

private:
	
	ShadersSourcePrograms ParseShaders();
	
	unsigned int CompileShader(unsigned int type, const std::string & source);
	
	unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	
	int GetUniformLocation(const std::string&);

};

