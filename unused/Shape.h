#pragma once

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Shape
{
public:
    Shape() {};
    Shape ( const void* vertexData, size_t vertexDataSize, const int* dataOffsets, int offsetsCount, const unsigned int* iboData, int iboDatacount);
    
    void init (const void* vertexData, size_t vertexDataSize, const int* dataOffsets, int offsetsCount, const unsigned int* iboData, int iboDatacount);

    unsigned getVAOID() const
    {
        return m_vao.getID();
    }
    //may not be needed
    
    void bindVAO() const
	{
		m_vao.bind();
	}
    void unbindVAO() const
    {
		m_vao.unbind();
	}
	

    
private:
    IndexBuffer m_ebo;
    VertexBuffer m_vbo;
    VertexArray m_vao;
	bool m_hasEBO;
};

//looks good. Tested. No need to come back to it.

//this is the unit square
/*
class Square: public Shape
{

public:
    
    static const GLfloat m_vertexData[12];
	static const unsigned m_vertexDataWidth;
    
	Square()
		:Shape(m_vertexData, 12 * sizeof(GLfloat), &m_vertexDataWidth, 1, nullptr, 0u)
	{}
	
	//static const Square instance;
};

*/
