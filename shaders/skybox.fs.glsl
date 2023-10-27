#version 450

uniform samplerCube skybox;

in vec3 texCoord;
out vec4 couleur;


void main()
{
    couleur = texture( skybox, texCoord );
    //couleur = vec4(1.0, 0.0, 0.0, 1.0);
}


