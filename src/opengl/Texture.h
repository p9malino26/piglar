#pragma once
#include <iostream>

#include <string>

class Texture
{
public:
    Texture(const std::string &fileName);
    Texture(Texture&& other);
    Texture();
	~Texture();
	//void activate(const std::string& name_in_shader, int slot, ShaderProg& shader) const;
    void init(const std::string& fileName);
    void activate(int slot) const;
    void bind() const;
    void unbind() const;
    inline GLuint getID() const {return m_rendererID;}
    inline bool good() const {return m_good;}
    

private:
    GLuint m_rendererID;
	
    bool m_good;
};
