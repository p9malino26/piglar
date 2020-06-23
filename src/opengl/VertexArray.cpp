#include <numeric>

#include "VertexArray.h"


VertexArray::VertexArray()
	:m_rendererID(0)
{
	glGenVertexArrays(1, &m_rendererID);
	//bind();
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_rendererID);
}

void VertexArray::bind() const 
{
	glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::specifyVertexAttributes(const int* offsets, int offsetsCount)
{
	int stride = std::accumulate(offsets, offsets + offsetsCount, 0) * sizeof(float);
	int byteOffset = 0;
	for(int i = 0; i < offsetsCount; i++)
	{
        glVertexAttribPointer(i, offsets[i], GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>( byteOffset));
		glEnableVertexAttribArray(i);
		byteOffset += (offsets[i] * sizeof(float));
	}
}

