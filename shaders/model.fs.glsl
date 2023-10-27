#version 450

uniform sampler2D laTexture;

in vec2 texCoord;
out vec4 couleur;


void main()
{
   
    //couleur = vec4(texCoord.x, texCoord.y, 0.0, 1.0);

    vec4 couleurText = texture( laTexture, texCoord );

    if (couleurText.a < 0.5){
        discard;
    }else{
        couleur = couleurText;
    }

     
		
}

