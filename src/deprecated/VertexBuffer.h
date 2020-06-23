#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

//#define GLEW_STATIC

#include <glad/glad.h>

#include <iostream>
#include <vector>

class VertexBuffer
{
public:
	VertexBuffer() {glGenBuffers(1, &m_rendererID);};
	VertexBuffer (const void* data, GLsizei size,  const int* offsets, int offsetsCount );
	~VertexBuffer();

	void init(const void* data, GLsizei size, const int* offsets, int offsetsCount );
	
    void bind() const;
    void unbind() const;
	
	inline GLuint getID() {return m_rendererID;}
private:
    GLuint m_rendererID; // the id of the VertexBuffer object
};

#endif //VERTEXBUFFER_H
