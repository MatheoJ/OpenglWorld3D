#version 330 core

uniform mat4 mvp;

layout(location = 0) in vec3 position;

out vec3 texCoord;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    texCoord = position;
}