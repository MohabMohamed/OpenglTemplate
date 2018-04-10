#pragma once






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

