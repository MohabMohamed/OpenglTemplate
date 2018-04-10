#include "GLErrorHandler.h"
#include <GL\glew.h>
#include <iostream>

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

