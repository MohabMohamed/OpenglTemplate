#pragma once
#include <vector>
#include <GL\glew.h>
#include "Renderer.h"
struct VertexBufferElement
{
	unsigned int type;
	unsigned int count;
	bool normalized;
	static unsigned int GetTypeSize(unsigned int type) 
	{
		switch (type)
		{
		case GL_UNSIGNED_BYTE:
			return 1;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_FLOAT:
			return 4;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_stride;
public:
	VertexBufferLayout():m_stride(0)
	{
	
	}
	~VertexBufferLayout() {}

	template <typename T>
	void Push(unsigned count) {

	}

	template <>
	void Push<float>(unsigned int count) 
	{
		m_Elements.push_back({ GL_FLOAT,count,false });
		m_stride += count * VertexBufferElement::GetTypeSize(GL_FLOAT);
	}

	template <>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT,count,false });
		m_stride += count *  VertexBufferElement::GetTypeSize(GL_UNSIGNED_INT);
	}

	template <>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE,count,true });
		m_stride += VertexBufferElement::GetTypeSize(GL_UNSIGNED_BYTE);
	}

	inline unsigned int GetStride() const { return m_stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const { return m_Elements; } //should add &
};


