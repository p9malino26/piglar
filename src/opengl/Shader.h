#ifndef SHADER_H
#define SHADER_H

//#define GLEW_STATIC
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <exception>


/**
 * @todo write docs
 */


class Shader
{
public:
    // Constructor generates the shader on the fly
    Shader() {}
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();
	void init(const std::string& vertexPath, const std::string& fragmentPath);
    // Uses the current shader
	
    void use() const {  glUseProgram( m_rendererID ); }
    void unUse() const {  glUseProgram( 0 ); }
	int getUniformLoc(const std::string& nameInShader) const;

	void uniformInt(const std::string& nameInShader, int x);
	void uniformMat4 (const std::string& nameInShader, const glm::mat4& mat);
    void uniformVec3 (const std::string& nameInShader, const glm::vec3& vec);
    void uniformVec4 (const std::string& nameInShader, const glm::vec4& vec);
	
    inline bool good() const {return m_good;}
    inline GLuint getID() const {return m_rendererID;}
private:
    void printLinkingErrorInfo() const;
	bool m_good;
	GLuint m_rendererID;
};



class ShaderUnit
{
public:
    ShaderUnit(const std::string& path, GLenum type);
    ~ShaderUnit();

	inline bool good() const {return m_good;}
	inline GLuint getID() const {return m_rendererID;}
private:
	void printErrorInfo(GLenum type) const;
	bool m_good;
	GLuint m_rendererID;

};



#endif
