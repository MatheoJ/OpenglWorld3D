#version 330 core

uniform mat4 mvp2;

layout(location = 0) in vec3 position;
layout(location=8) in vec2 TexCoord;

out vec2 texCoord;

void main()
{
    gl_Position = mvp2 * vec4(position, 1.0);
    texCoord = TexCoord.st;
}