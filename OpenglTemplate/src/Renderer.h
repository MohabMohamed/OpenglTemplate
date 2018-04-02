#pragma once

#include <GL\glew.h>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

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


class Renderer
{
public:
	Renderer();
	~Renderer();
	void Clear() const; 
	void Draw(const VertexArray&, const IndexBuffer&, const Shader&) const;
private:

};


