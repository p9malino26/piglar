#ifndef BUFFER_H
#define BUFFER_H

#include <glad/glad.h>

class Buffer
{
public:
    Buffer();
    Buffer (unsigned int type, const void* data, int size);
	~Buffer();

    void init(unsigned int type, const void* data, int size);
	
    void bind() const;
    void unbind() const;
	
	inline unsigned int getID() {return m_rendererID;}
private:
    unsigned int m_type;
    unsigned int m_rendererID; // the id of the VertexBuffer object

};

#endif
