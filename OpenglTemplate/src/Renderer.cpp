#include "Renderer.h"
#include <iostream>

#pragma region GlError
void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);

}
bool GLLogError(const char* function, const char* file, int line)
{
	while (GLenum err = glGetError())
	{
		std::cout << "[OpenGL Error] (" << err << ")	file :" << file << "\n	function : " <<
			function << "\n	line : " << line << std::endl;
		return false;
	}
	return true;
}

#pragma endregion

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();
	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
