#pragma once

#include <glad/glad.h>
#include <string>

class GLUtils {
public:
    GLUtils();
    ~GLUtils();

    static void loadShader(const std::string& shaderSource, GLenum shaderType, unsigned int &programId);
};

