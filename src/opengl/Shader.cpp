#include <glad/glad.h>
#include "Shader.h"

enum class UnitType
{
    SHADER, PROGRAM
};

namespace{
	std::string getShaderSourceFromFile(const std::string& fileName);

	void printErrorInfoGeneric(GLuint unit, UnitType type);
	void checkForUniformExistence(int location, const std::string& uniformName);
}

Shader::Shader( const std::string& vertexPath, const std::string& fragmentPath )
{
    init(vertexPath, fragmentPath);
}

void Shader::init(const std::string& vertexPath, const std::string& fragmentPath)
{
	m_good = true;
	this->m_rendererID = glCreateProgram( );
	// 1. Retrieve the vertex/fragment source code from filePath

    try
    {
        ShaderUnit vertexShader(vertexPath, GL_VERTEX_SHADER);
        ShaderUnit fragmentShader(fragmentPath, GL_FRAGMENT_SHADER);
        if ( !(vertexShader.good() && fragmentShader.good()) )
        {
            /*m_vsGood = false;*/
			
            throw std::exception();
        }


        // Shader Program

        glAttachShader( this->m_rendererID, vertexShader.getID() );
        glAttachShader( this->m_rendererID, fragmentShader.getID() );
        glLinkProgram( this->m_rendererID );
        // Print linking errors if any
        GLint success;
        glGetProgramiv( this->m_rendererID, GL_LINK_STATUS, &success );
        if (!success)
        {
            printLinkingErrorInfo();
            throw std::exception();

        }
    }catch (std::exception&)
    {
        m_good = false;
    }
	// Delete the shaders as they're linked into our program now and no longer necessery

}

void Shader::use() const {  glUseProgram( m_rendererID ); }
void Shader::unUse() const {  glUseProgram( 0 ); }

void Shader::printLinkingErrorInfo() const
{
	std::cerr << "[ERROR] Shader program linking failed." << std::endl;

	printErrorInfoGeneric(m_rendererID, UnitType::PROGRAM);
}

Shader::~Shader()
{
	glDeleteProgram(m_rendererID);
}


ShaderUnit::ShaderUnit ( const std::string &path, GLenum type )
:m_good(true)
{
	try
	{
		std::string source = getShaderSourceFromFile(path);
		const GLchar* sourceRaw = source.c_str();
		m_rendererID = glCreateShader(type);
		glShaderSource(m_rendererID, 1, &sourceRaw, nullptr);
		glCompileShader(m_rendererID);
		//get the error state information/query for the shader
		GLint success;
		glGetShaderiv( m_rendererID, GL_COMPILE_STATUS, &success);
		//if the result is false or if the shader did not compile successfully
		if(!success)
		{
			printErrorInfo(type);
			throw std::exception();
		}
	}catch (std::exception&)
	{
		m_good = false;
	}
}

ShaderUnit::~ShaderUnit()
{
	glDeleteShader(m_rendererID);
}


void ShaderUnit::printErrorInfo(GLenum type) const
{
	std::cerr << "[ERROR] " << ( (type == GL_VERTEX_SHADER) ? "Vertex" : "Fragment" ) << " shader compilation failed." << std::endl;

	printErrorInfoGeneric(m_rendererID, UnitType::SHADER);
}

namespace{
	std::string getShaderSourceFromFile(const std::string& fileName)
	{
		std::ifstream file;
		file.open(fileName);
		if(!file.is_open())
		{
			std::cout << "Error. File not found: \"" << fileName << "\"" << std::endl;
			throw std::exception();
			return std::string();
		}

		std::stringstream sourceBuf;

		sourceBuf << file.rdbuf() << '\n';

		file.close();
        return sourceBuf.str();

		

	}

    void printErrorInfoGeneric(GLuint unit, UnitType type)
    {
		GLint infoLogLength;
		((type == UnitType::PROGRAM) ? glGetProgramiv: glGetShaderiv) (unit, GL_INFO_LOG_LENGTH, &infoLogLength);
		char* infoLog;
		infoLog = new char[infoLogLength];
		((type == UnitType::PROGRAM) ? glGetProgramInfoLog: glGetShaderInfoLog) (unit, infoLogLength, &infoLogLength, infoLog);

		std::cerr << infoLog << std::endl;
		delete[] infoLog;
	}

	void checkForUniformExistence(int location, const std::string& uniformName)
	{
		if(location == -1)
		{
			std::cerr << "[ERROR] Uniform \"" << uniformName << "\" does not exist." << std::endl;
		}
	}
}

int Shader::getUniformLoc(const std::string& nameInShader) const
{
	return glGetUniformLocation(m_rendererID, nameInShader.c_str());
}

void Shader::uniformInt(const std::string& nameInShader, int x) const
{
	//use();
	int uniform_loc = getUniformLoc(nameInShader);
	checkForUniformExistence(uniform_loc, nameInShader);
	glUniform1i(uniform_loc, x);
}

void Shader::uniformMat4 (const std::string& nameInShader, const glm::mat4& mat) const
{
	//use();
	int mat_loc = getUniformLoc(nameInShader);
	checkForUniformExistence(mat_loc, nameInShader);
	glUniformMatrix4fv( mat_loc, 1, GL_FALSE, glm::value_ptr( mat ));
}

void Shader::uniformVec3(const std::string& nameInShader, const glm::vec3& vec) const
{
	//use();
	int vec_loc = getUniformLoc(nameInShader);
	checkForUniformExistence(vec_loc, nameInShader);
	glUniform3f(vec_loc, vec.x, vec.y, vec.z);

}

void Shader::uniformVec4(const std::string& nameInShader, const glm::vec4& vec) const
{
	//use();
	int vec_loc = getUniformLoc(nameInShader);
	checkForUniformExistence(vec_loc, nameInShader);
    glUniform4f(vec_loc, vec.x, vec.y, vec.z, vec.w);
}
