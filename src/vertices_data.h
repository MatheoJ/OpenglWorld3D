#ifndef VERTICES_DATA_H
#define VERTICES_DATA_H



const GLfloat groundVertices[]{
        //Position              //Texture coordinates
       -30.0f,0.0f,  -30.0f, 0.0f, 0.0f,
       30.0f, 0.0f, -30.0f, 10.0f, 0.0f,
       -30.0f,0.0f,  30.0f, 0.0f, 10.0f,
        30.0f,0.0f,  30.0f, 10.0, 10.0f,
};

const GLuint groundIndexes[]{
    2, 1, 0, // first triangle
    1, 2, 3  // second triangle
};

const GLfloat riverVertices[]{
        //Position              //Texture coordinates
       -30.0f,  0.0f,  -30.0f, 0.0f, 0.0f,
       30.0f,   0.0f, -30.0f, 10.0f, 0.0f,
       30.0f,   0.0f,  -50.0f,  10.0f, 4.0f,
        -30.0f, 0.0f,  -50.0f,  0.0f, 4.0f,
};

const GLuint riverIndexes[]{
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

float heartVertices[] = {
    // Positions   // Texture Coords
    -0.5f, -0.5f,0.0f,    0.0f, 0.0f,
    0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
    0.5f, 0.5f,  0.0f, 1.0f, 1.0f,
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f
};

const GLuint heartIndexes[]{
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};

float billboardVertices[] = {
    // Positions    // Texture Coords
    -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,
     0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
     0.5f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f, 1.0f, 0.0f, 0.0f, 1.0f
};

const GLuint billboardIndexes[]{
    0, 1, 2, // first triangle
    0, 2, 3  // second triangle
};


const GLfloat cubeVertices[] = {
    // +z
    -60.0f, -60.0f,  60.0f,
     60.0f, -60.0f,  60.0f,
    -60.0f,  60.0f,  60.0f,
     60.0f,  60.0f,  60.0f,
     // -z
    -60.0f, -60.0f, -60.0f,
     60.0f, -60.0f, -60.0f,
    -60.0f,  60.0f, -60.0f,
     60.0f,  60.0f, -60.0f,
     // +x
     60.0f, -60.0f, -60.0f,
     60.0f, -60.0f,  60.0f,
     60.0f,  60.0f, -60.0f,
     60.0f,  60.0f,  60.0f,
     // -x
    -60.0f, -60.0f, -60.0f,
    -60.0f, -60.0f,  60.0f,
    -60.0f,  60.0f, -60.0f,
    -60.0f,  60.0f,  60.0f,
     // +y
    -60.0f,  60.0f, -60.0f,
     60.0f,  60.0f, -60.0f,
    -60.0f,  60.0f,  60.0f,
     60.0f,  60.0f,  60.0f,
     // -y
    -60.0f, -60.0f, -60.0f,
     60.0f, -60.0f, -60.0f,
    -60.0f, -60.0f,  60.0f,
     60.0f, -60.0f,  60.0f,
};

const GLuint cubeIndexes[] = {
     0,  1,  2,
     1,  3,  2,
    
     4,  5,  6,
     5,  7,  6,
    
     8,  9, 10,
     9, 11, 10,
    
    12, 13, 14,
    13, 15, 14,
    
    16, 17, 18,
    17, 19, 18,
    
    20, 21, 22,
    21, 23, 22,
};

const GLfloat grassPosition[] = {
    0.433013f, 0.0f, -0.25f,
    -0.433013f, 0.75f, 0.25f,
    0.433013f, 0.75f, -0.25f,

    0.433013f,  0.0f,  -0.25f,
    -0.433013f, 0.0f,  0.25f,
    -0.433013f,  0.75f,  0.25f,

    0.0f     ,  0.0f, -0.5f,
    0.0f     ,  0.75f,  0.5f,
    0.0f     ,  0.0f,  0.5f,

    0.0f     ,  0.0f, -0.5f,
    0.0f     ,  0.75f, -0.5f,
    0.0f     ,  0.75f,  0.5f,

    -0.433013f,  0.0f, -0.25f,
    0.433013f,  0.75f,  0.25f,
    0.433013f,  0.0f,  0.25f,

    -0.433013f,  0.0f, -0.25f,
    -0.433013f,  0.75f, -0.25f,
    0.433013f,  0.75f,  0.25f,
};

const GLfloat grassTexCoords[] = {
    0.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,

    0.0f, 0.0f,
    1.0f, 0.0f,
    1.0f, 1.0f,


    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,


    1.0f, 0.0f,
    0.0f, 1.0f,
    0.0f, 0.0f,

    1.0f, 0.0f,
    1.0f, 1.0f,
    0.0f, 1.0f,
};

#endif // VERTICES_DATA_H
