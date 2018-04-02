#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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

//set uniforms
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4f(const std::string & name, glm::mat4 & mat);
private:
	ShadersSourcePrograms ParseShaders();
	unsigned int CompileShader(unsigned int type, const std::string & source);
	unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	int GetUniformLocation(const std::string&);

};

