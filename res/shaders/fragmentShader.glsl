#version 330 core

in vec2 texCoord;

uniform vec3 inColor;
uniform sampler2D theTexture;
uniform bool showTexture;

out vec4 color;

void main()
{
    if (showTexture) {
        color = texture(theTexture, texCoord);
        if (color.a < 0.1)
            discard;
    } else {
        color = vec4(inColor, 1.0);
    }
}
