#version 450

uniform sampler2D laTexture;
uniform float time;

in vec2 texCoord;
out vec4 couleur;


void main()
{
    vec2 newTextCoord =  vec2(0,0);
    vec2 timeScale = vec2(1,2);
    vec2 offsetScale = vec2(2,2);


    newTextCoord.x =   texCoord.x + 0.035*cos(  time * timeScale.x + (texCoord.x + texCoord.y)*offsetScale.x);
    newTextCoord.y =  texCoord.y + 0.002*sin( time * timeScale.y + (texCoord.x + texCoord.y)*offsetScale.y);
    //Log time


    couleur = texture( laTexture, newTextCoord);
}