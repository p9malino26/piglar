#version 330 core
layout (location = 0) in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform mat4 textureTransform;

out vec2 texCoord;

void main()
{
    gl_Position =  proj * view * model * vec4(position, 0.0, 1.0);
    texCoord = (textureTransform * vec4(position, 0, 1)).xy;
}
