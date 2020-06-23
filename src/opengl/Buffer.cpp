#include "Buffer.h"

Buffer::Buffer()
    :m_type(0)
{
    glGenBuffers(1, &m_rendererID);
}

Buffer::Buffer (unsigned int type, const void* data, int size)
{
    glGenBuffers(1, &m_rendererID);
    init(type, data, size);
}

void Buffer::init(unsigned int type, const void* data, int size)
{
    m_type = type;
    bind();
    glBufferData(m_type, size, data, GL_STATIC_DRAW);
    unbind();
}

void Buffer::bind() const
{
    glBindBuffer(m_type, m_rendererID);
}

void Buffer::unbind() const
{
    glBindBuffer(m_type, 0);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &m_rendererID);
}
