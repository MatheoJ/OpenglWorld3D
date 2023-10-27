#version 330 core

in vec2 exCoords;
uniform sampler2D grassTexture;

out vec4 FragColor;

void main()
{
    vec4 texColor = texture(grassTexture, exCoords);
    if(texColor.a < 0.1) 
        discard;  
    FragColor = texColor;
}