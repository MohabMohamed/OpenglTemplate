#pragma once
#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <unordered_map>
#include <GL\glew.h>
//#include "Renderer.h"



#pragma region GlError

#define ASSERT(x) if(!(x)) __debugbreak();
#ifdef _DEBUG
#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogError(#x, __FILE__, __LINE__))
#else
#define GLCall(x) x //Re
#endif // DEBUG

void GLClearError();
bool GLLogError(const char* function, const char* file, int line);

#pragma endregion


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

	template <typename... Rest>
	void SetUniformElements(const std::string & name, float f0, Rest... uniforms)
	{
		
		switch (sizeof...(uniforms))
		{
		case 0:
			glUniform1f(GetUniformLocation(name), f0);
			break;
		case 1:
			glUniform2f(GetUniformLocation(name), f0, std::forward<Rest>(uniforms)...);
			
			break;
		case 2:
			glUniform3f(GetUniformLocation(name), f0, std::forward<Rest>(uniforms)...);
			break;
		case 3:
			glUniform4f(GetUniformLocation(name), f0, std::forward<Rest>(uniforms)...);
			break;
		default:
			std::cout << "warning wrong paramters number for set uniform\n";
			break;
		}

	}


	template <typename... Rest>
	void SetUniformElements(const std::string & name, unsigned int ui0, Rest... uniforms)
	{
		switch (sizeof...(uniforms))
		{
		case 0:
			GLCall(glUniform1ui(GetUniformLocation(name), ui0, std::forward<Rest>(uniforms)...));
			break;
		case 1:
			GLCall(glUniform2ui(GetUniformLocation(name), ui0, std::forward<Rest>(uniforms)...));
			break;
		case 2:
			GLCall(glUniform3ui(GetUniformLocation(name), ui0, std::forward<Rest>(uniforms)...));
			break;
		case 3:
			GLCall(glUniform4ui(GetUniformLocation(name), ui0, std::forward<Rest>(uniforms)...));
			break;
		default:
			std::cout << "warning wrong paramters number for set uniform\n";
			break;
		}

	}

	template <typename... Rest>
	void SetUniformElements(const std::string & name, int i0, Rest... uniforms)
	{
		switch (sizeof...(uniforms))
		{
		case 0:
			GLCall(glUniform1i(GetUniformLocation(name), i0, std::forward<Rest>(uniforms)...));
			break;
		case 1:
			GLCall(glUniform2i(GetUniformLocation(name), i0, std::forward<Rest>(uniforms)...));
			break;
		case 2:
			GLCall(glUniform3i(GetUniformLocation(name), i0, std::forward<Rest>(uniforms)...));
			break;
		case 3:
			GLCall(glUniform4i(GetUniformLocation(name), i0, std::forward<Rest>(uniforms)...));
			break;
		default:
			std::cout << "warning wrong paramters number for set uniform\n";
			break;
		}

	}
	

	void SetUniformMat4f(const std::string & name, glm::mat4 & mat);
private:
	ShadersSourcePrograms ParseShaders();
	unsigned int CompileShader(unsigned int type, const std::string & source);
	unsigned int CreateShader(const std::string & vertexShader, const std::string & fragmentShader);
	int GetUniformLocation(const std::string&);



	

};

