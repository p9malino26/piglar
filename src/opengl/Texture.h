#ifndef TEXTURE_H
#define TEXTURE_H


#include <glad/glad.h>
#include <iostream>

#include <string>



class Texture
{
public:
    Texture(const std::string &fileName);
    Texture();
	~Texture();
	//void activate(const std::string& name_in_shader, int slot, ShaderProg& shader) const;
    void init(const std::string& fileName);
    void activate(int slot) const;
    void bind() const;
    void unbind() const;
    inline GLuint getID() const {return m_rendererID;}
	inline int getWidth() const{return m_width;}
	inline int getHeight() const{return m_height;}
    inline bool good() const {return m_good;}
    

private:
    GLuint m_rendererID;
	std::string m_fileName;
	
    bool m_good;
    int m_width, m_height, m_nChannels /*m_bitsPerPix*/;
};

#endif // TEXTURE_H
