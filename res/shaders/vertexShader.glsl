#version 330 core
layout (location = 0) in vec2 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;
uniform bool isWorld;
uniform bool transformToCamera;
uniform mat4 textureTransform;

out vec2 texCoord;

void main()
{
    mat4 world2NDC = proj * view;
    gl_Position = model * vec4(position, 0.0, 1.0);

    if (isWorld)
        gl_Position = world2NDC * gl_Position;

    if (transformToCamera)
        texCoord = (inverse(world2NDC * textureTransform) * gl_Position).xy;
    else
        texCoord = (textureTransform * vec4(position, 0, 1)).xy;
}
