#version 330 core

uniform sampler2D pigTex;
in vec2 vTexCoord;
in vec3 vColor;


out vec4 color;

void main()
{
    color = texture(pigTex, vTexCoord) * vec4(vColor, 1.0);
}