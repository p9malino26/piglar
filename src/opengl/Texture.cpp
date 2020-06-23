#include "Texture.h"

#include <stb_image/stb_image.h>

Texture::Texture()
{
	glGenTextures(1, &m_rendererID);
}

Texture::Texture(const std::string& fileName)
{
	glGenTextures(1, &m_rendererID);
	init(fileName);
}

void Texture::init(const std::string& fileName)
{
	m_good = true;
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//float borderColor[] = {};
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	//load the data
	stbi_set_flip_vertically_on_load(true);
	unsigned char* m_imageData = stbi_load(fileName.c_str(), &m_width, &m_height, &m_nChannels, 4);
	if (m_imageData == nullptr)
	{
		std::cerr << "[ERROR] Failed to load Texture: \"" << fileName << "\" . File not found." << std::endl;
		m_good = false;
		
	}
	//specify the data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imageData );
	glGenerateMipmap(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(m_imageData);
	unbind();
}


Texture::~Texture()
{
	glDeleteTextures(1, &m_rendererID);
}


void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_rendererID);
}

/* void Texture::activate ( const std::string& name_in_shader, int slot, ShaderProg& shader) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	bind();
	int uniformLoc = shader.getUniformLoc(name_in_shader);
	assert(uniformLoc != -1);
	shader.use();
	glUniform1i(uniformLoc, slot);
}*/

void Texture::activate(int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	bind();
}


void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
