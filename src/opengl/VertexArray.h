#pragma once

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
    unsigned int m_rendererID;
};
