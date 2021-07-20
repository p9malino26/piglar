#version 330 core

in vec2 texCoord;

uniform vec3 inColor;
uniform vec3 chromaColor;
uniform bool chromaKey;
uniform sampler2D theTexture;
uniform bool showTexture;

out vec4 color;

void main()
{
    if (showTexture) {
        color = texture(theTexture, texCoord);
        if (color.a < 0.1)
            if (chromaKey)
                color = vec4(chromaColor, 1.0);
            else
                discard;
    } else {
        color = vec4(inColor, 1.0);
    }
}
