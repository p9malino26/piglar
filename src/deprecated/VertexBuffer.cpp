#include <numeric>

#include "VertexBuffer.h"


VertexBuffer::VertexBuffer(const void* data, GLsizei size, const int* offsets, int offsetsCount)
{
    glGenBuffers(1, &m_rendererID);
    init(data, size, offsets, offsetsCount);
}


void VertexBuffer::init(const void* data, GLsizei size, const int* offsets, int offsetsCount )
{
    
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	int stride = std::accumulate(offsets, offsets + offsetsCount, 0) * sizeof(float);
	int byteOffset = 0;
	for(int i = 0; i < offsetsCount; i++)
	{
        glVertexAttribPointer(i, offsets[i], GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>( byteOffset));
		glEnableVertexAttribArray(i);
		byteOffset += (offsets[i] * sizeof(float));
		
	}
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
}


VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_rendererID);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


