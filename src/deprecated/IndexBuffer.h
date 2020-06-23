#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

//#define GLEW_STATIC
#include <glad/glad.h>

#include <iostream>

class IndexBuffer
{
public:
    IndexBuffer() { glGenBuffers(1, &m_rendererID);}
    IndexBuffer(const GLuint* data, int count);
    ~IndexBuffer();

    void init(const GLuint* data, int count);
    void bind() const;
    void unbind() const;

    inline int getCount() const {return m_count; }
    inline GLuint getID() {return m_rendererID;}
private:
    GLuint m_rendererID; // the id of the VertexBuffer object
    GLuint m_count;
};

#endif // INDEXBUFFER_H
