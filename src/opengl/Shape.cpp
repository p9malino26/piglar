#include "Shape.h"



Shape::Shape(const void* vertexData, size_t vertexDataSize, const int* dataOffsets, int offsetsCount, const unsigned int* iboData, int iboDatacount)
{
    init(vertexData, vertexDataSize, dataOffsets, offsetsCount,iboData, iboDatacount);
}


void Shape::init ( const void* vertexData, size_t vertexDataSize, const int* dataOffsets, int offsetsCount, const unsigned int* iboData, int iboDatacount)
{
	m_hasEBO = (iboData != nullptr);

	m_vao.bind();	
	m_vbo.init(vertexData, vertexDataSize, dataOffsets, offsetsCount);
	if( m_hasEBO ) { m_ebo.init(iboData, iboDatacount);}
	m_vao.unbind();
	m_vbo.unbind();
	if( m_hasEBO ) {m_ebo.unbind();}
}


/* const GLfloat Square::m_vertexData[12] = 
{
    0.0f, 1.0f,//tl
    1.0f, 1.0f,//tr
    1.0f, 0.0f,//br

    0.0f, 1.0f,//tl
    0.0f, 0.0f,//bl
    1.0f, 0.0f//br
};

const unsigned Square::m_vertexDataWidth = 2;*/
