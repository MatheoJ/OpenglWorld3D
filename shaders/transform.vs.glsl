#version 330 core

uniform mat4 mvp;

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
out vec3 vColor;

void main()
{
    gl_Position = mvp * vec4(position, 1.0);
    vColor = color;
}