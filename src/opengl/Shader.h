#pragma once

#include <glad/glad.h>

#include "../GLMIncludes.h"

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
	
    void use() const;
    void unUse() const;

	int getUniformLoc(const std::string& nameInShader) const;

	void uniformInt(const std::string& nameInShader, int x) const;
	void uniformMat4 (const std::string& nameInShader, const glm::mat4& mat) const;
    void uniformVec3 (const std::string& nameInShader, const glm::vec3& vec) const;
    void uniformVec4 (const std::string& nameInShader, const glm::vec4& vec) const;
	
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
