#version 330 core

layout(location = 0) in vec3 inPos;
layout(location = 8) in vec2 inTexCoords;

uniform mat4 mvp;
uniform float time;

out vec2 exCoords;

void main()
{
    exCoords = inTexCoords;
    vec3 pos = inPos;
    pos.xz += inTexCoords.y * sin(time + pos.x + pos.z) * 0.1;
    gl_Position = mvp * vec4(pos, 1.0);
}