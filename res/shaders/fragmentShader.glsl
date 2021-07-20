#version 330 core

in vec2 texCoord;

uniform vec3 inColor;
uniform vec3 chromaReplace;
uniform bool chromaKey;
uniform sampler2D theTexture;
uniform bool showTexture;

out vec4 color;

void main()
{
    if (showTexture) {
        vec4 texColor = texture(theTexture, texCoord);
        if (texColor.x + texColor.y + texColor.z > 2.9 && chromaKey)
            color = vec4(chromaReplace, 1.0);
        else if (texColor.a < 0.1)
            discard;
        else
            color = texColor;
    } else {
        color = vec4(inColor, 1.0);
    }
}
