#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

//#define GLEW_STATIC
#include <glad/glad.h>

/**
 * @todo write docs
 */
class VertexArray
{
public:
	VertexArray();
	~VertexArray();
    void bind() const;

    void unbind() const;

	void specifyVertexAttributes(const int* offsets, int offsetsCount);
	
	unsigned getID() const
	{
		return m_rendererID;
	}
	
	
private:
    GLuint m_rendererID;
};

#endif // VERTEXARRAY_H
