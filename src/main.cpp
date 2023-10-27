
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "window.h"
#include "shader_program.h"
#include "vertices_data.h"
#include "shapes.h"
#include "camera.h"
#include "model.h"
#include "utils.h"
#include "textures.h"


void printGLInfo();

#define GL_CHECK_ERROR checkGLError(__LINE__)
void checkGLError(int line);

std::string readFile(const char* path);

void genTransformForGroup(GLint N_ROWS, glm::mat4* groupsTransform, glm::mat4* treeTransform, glm::mat4* rockTransform, glm::mat4* shroomTransform);

void updateCameraWithKeyboard(Window& w, float speed, glm::vec3& camPosition, glm::vec2& camOrientation, Camera& camera);

void genGrass(std::vector<BasicShapeMultipleArrays *>& grasses, int N_GRASS,const GLfloat grassPosition[], const GLint posSize,const GLfloat grassTexCoords[], const GLint textSize);

int main(int argc, char* argv[])
{
    Window w;
    if (!w.init())
        return -1;
    
    GLenum rev = glewInit();
    if ( rev != GLEW_OK )
    {
        std::cout << "Could not initialize glew! GLEW_Error: " << glewGetErrorString(rev) << std::endl;
        return -2;
    }

    ShaderProgram modelShader;
    GLint locMVP;
    GLint locText;
    {
		std::string srcVertex = readFile("../shaders/model.vs.glsl");
		std::string srcFragment = readFile("../shaders/model.fs.glsl");

		const char* codeVertex = srcVertex.c_str();
		const char* codeFragment = srcFragment.c_str();

		Shader vertexShader(GL_VERTEX_SHADER, codeVertex);
		Shader fragmentShader(GL_FRAGMENT_SHADER, codeFragment);

        modelShader.attachShader(vertexShader);
        modelShader.attachShader(fragmentShader);
        modelShader.link();

        modelShader.use();

		locMVP = modelShader.getUniformLoc("mvp2");
        locText = modelShader.getUniformLoc("laTexture");        
	}

    ShaderProgram waterShader;
    GLint locMVPWater;
    GLint locTextWater;
    GLint locTime;
    {
        std::string srcVertex = readFile("../shaders/water.vs.glsl");
        std::string srcFragment = readFile("../shaders/water.fs.glsl");

        const char* codeVertex = srcVertex.c_str();
        const char* codeFragment = srcFragment.c_str();

        Shader vertexShader(GL_VERTEX_SHADER, codeVertex);
        Shader fragmentShader(GL_FRAGMENT_SHADER, codeFragment);

        waterShader.attachShader(vertexShader);
        waterShader.attachShader(fragmentShader);
        waterShader.link();

        waterShader.use();

        locMVPWater = waterShader.getUniformLoc("mvp2");
        locTextWater = waterShader.getUniformLoc("laTexture");
        std::cout << "locTextWater" << locTextWater << std::endl;
        locTime = waterShader.getUniformLoc("time");
        std::cout << "locTime" << locTime << std::endl;

    }

    ShaderProgram skyBoxShader;
    GLint locMVPSkyBox;
    GLint locTextSkyBox;

    {
		std::string srcVertex = readFile("../shaders/skybox.vs.glsl");
		std::string srcFragment = readFile("../shaders/skybox.fs.glsl");

		const char* codeVertex = srcVertex.c_str();
		const char* codeFragment = srcFragment.c_str();

		Shader vertexShader(GL_VERTEX_SHADER, codeVertex);
		Shader fragmentShader(GL_FRAGMENT_SHADER, codeFragment);

		skyBoxShader.attachShader(vertexShader);
		skyBoxShader.attachShader(fragmentShader);
		skyBoxShader.link();

		skyBoxShader.use();

		locMVPSkyBox = skyBoxShader.getUniformLoc("mvp");
		locTextSkyBox = skyBoxShader.getUniformLoc("skybox");
	}

    ShaderProgram grassShader;
    GLint locMVPGrass;
    GLint locTextGrass;
    GLint locTimeGrass;
    {
		std::string srcVertex = readFile("../shaders/gazon.vs.glsl");
		std::string srcFragment = readFile("../shaders/gazon.fs.glsl");

		const char* codeVertex = srcVertex.c_str();
		const char* codeFragment = srcFragment.c_str();

		Shader vertexShader(GL_VERTEX_SHADER, codeVertex);
		Shader fragmentShader(GL_FRAGMENT_SHADER, codeFragment);

		grassShader.attachShader(vertexShader);
		grassShader.attachShader(fragmentShader);
		grassShader.link();

		grassShader.use();

		locMVPGrass = grassShader.getUniformLoc("mvp");
		locTextGrass = grassShader.getUniformLoc("grassTexture");
        locTimeGrass = grassShader.getUniformLoc("time");
	}

    
    
    float angleDeg = 0.0f;
    
    
    BasicShapeElements cube;
    cube.setData(cubeVertices, sizeof(cubeVertices), cubeIndexes, sizeof(cubeIndexes));
    cube.enableAttribute(0, 3, 6 * sizeof(GLfloat), 0);
    cube.enableAttribute(1, 3, 6 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    BasicShapeElements ground; 
    ground.setData(groundVertices, sizeof(groundVertices), groundIndexes, sizeof(groundIndexes));
    ground.enableAttribute(0, 3, 5 * sizeof(GLfloat), 0);
    ground.enableAttribute(8, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    BasicShapeElements river;
    river.setData(riverVertices, sizeof(riverVertices), riverIndexes, sizeof(riverIndexes));
    river.enableAttribute(0, 3, 5 * sizeof(GLfloat), 0);
    river.enableAttribute(8, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    BasicShapeElements heart;
    heart.setData(heartVertices, sizeof(heartVertices), heartIndexes, sizeof(heartIndexes));
    heart.enableAttribute(0, 3, 5 * sizeof(GLfloat), 0);
    heart.enableAttribute(8, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));

    BasicShapeElements skyBox;
    skyBox.setData(cubeVertices, sizeof(cubeVertices), cubeIndexes, sizeof(cubeIndexes));
    skyBox.enableAttribute(0, 3, 0, 0);

    BasicShapeElements billboard;
    billboard.setData(billboardVertices, sizeof(billboardVertices), billboardIndexes, sizeof(billboardIndexes));
    billboard.enableAttribute(0, 3, 5 * sizeof(GLfloat), 0);
    billboard.enableAttribute(8, 2, 5 * sizeof(GLfloat), 3 * sizeof(GLfloat));


    std::vector<BasicShapeMultipleArrays* > grasses;
    genGrass(grasses, 500, grassPosition, sizeof(grassPosition) / sizeof(GLfloat), grassTexCoords, sizeof(grassTexCoords) / sizeof(GLfloat));


    Model tree("../models/tree.obj");
    Model rock("../models/rock.obj");
    Model shroom("../models/mushroom.obj");
    Model suzanne("../models/suzanne.obj");

    Texture2D textTree ("../models/treeTexture.png", GL_CLAMP_TO_BORDER);  
    Texture2D textRock("../models/rockTexture.png", GL_CLAMP_TO_BORDER);
    Texture2D textShroom("../models/mushroomTexture.png", GL_CLAMP_TO_BORDER);
    Texture2D textSuzanne("../models/suzanneTexture.png", GL_CLAMP_TO_BORDER);
    Texture2D textGround("../textures/groundSeamless.jpg", GL_REPEAT);
    Texture2D textRiver("../textures/waterSeamless.jpg", GL_REPEAT);
    Texture2D textHeart("../textures/heart.png", GL_REPEAT);
    Texture2D treeBillboard("../textures/treeBillboard.png", GL_CLAMP_TO_BORDER);
    Texture2D textGrass("../textures/grassAtlas.png", GL_CLAMP_TO_BORDER);

    const char* pathes[6] = {
        "../textures/skybox/Daylight Box_Right.bmp",
        "../textures/skybox/Daylight Box_Left.bmp",
        "../textures/skybox/Daylight Box_Top.bmp",
        "../textures/skybox/Daylight Box_Bottom.bmp",
        "../textures/skybox/Daylight Box_Front.bmp",             
		"../textures/skybox/Daylight Box_Back.bmp"
	};
    TextureCubeMap textSkyBox(pathes);



    const int N_ROWS = 7;
    const int N_GROUPS = N_ROWS * N_ROWS;

    glm::mat4 groupsTransform[N_GROUPS];

    glm::mat4 treeTransform[N_GROUPS];
    glm::mat4 rockTransform[N_GROUPS];
    glm::mat4 shroomTransform[N_GROUPS];

    
	genTransformForGroup(N_ROWS, groupsTransform, treeTransform, rockTransform, shroomTransform);
  
       
    //Activer le depth test.
    glEnable(GL_DEPTH_TEST);

 
    float speed = 0.05f;

    glm::vec3 camPosition(0.0f, 1.2f, -2.0f); // Camera position
    glm::vec2 camOrientation(0.0f, 0.0f); // Camera orientation (yaw, pitch)

    Camera camera(camPosition, camOrientation);
    
    bool isRunning = true;
    while (isRunning)
    {
        if (w.shouldResize())
            glViewport(0, 0, w.getWidth(), w.getHeight());
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        updateCameraWithKeyboard(w, speed, camPosition, camOrientation, camera);

        modelShader.use();
        glUniform1i(locText, 0);
        
        waterShader.use();
		glUniform1i(locTextWater, 0);

        skyBoxShader.use();
        glUniform1i(locTextSkyBox, 0);

        grassShader.use();
        glUniform1i(locTextGrass, 0);


        // Create Model matrix
        glm::mat4 model = glm::mat4(1.0f);

        // Create Vmatrix
        glm::mat4 view;
        if (camera.getMode() == CameraMode::FirstPerson) {
            view = camera.getFirstPersonViewMatrix();
        }
        else {
            view = camera.getThirdPersonViewMatrix();
        }


        glm::mat4 orthProjection = glm::ortho(0.0f, (float)w.getWidth(), 0.0f, (float)w.getHeight(), 1.0f, -1.0f);       
          
        
        //Scale and translate heart
        model = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f,0.0f));
        model = glm::scale(model, glm::vec3(100.0f, 100.0f, 0.0f));
        glm::mat4 mvp = orthProjection * model;


        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);


        glDepthFunc(GL_ALWAYS);
        modelShader.use();
        glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
        textHeart.use();
        heart.draw(GL_TRIANGLES, 6);
        glDepthFunc(GL_LESS);

        model = glm::mat4(1.0f);

        // Create Projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(70.0f), (float)w.getWidth() / (float)w.getHeight(), 0.1f, 200.0f);

        // Combine all the matrices to create the MVP matrix
        mvp = projection * view * model;


        waterShader.use();
        glUniformMatrix4fv(locMVPWater, 1, GL_FALSE, &mvp[0][0]);
        float time = w.getTick();
        glUniform1f(locTime, time/1000.0f);
        textRiver.enableMipmap();
        textRiver.use();
        river.draw(GL_TRIANGLES, 6);


        modelShader.use();

        // If 3rd person, generate suzanne
        if (camera.getMode() == CameraMode::ThirdPerson) {
            glm::mat4 suzanneModelMatrix = glm::translate(glm::mat4(1.0f), camPosition);
            suzanneModelMatrix = glm::rotate(suzanneModelMatrix, camOrientation.x + glm::radians(180.0f), glm::vec3(0.0f, -1.0f, 0.0f));
            float suzanneScale = 0.5f; // Ajustez cette valeur pour changer la taille de Suzanne
            suzanneModelMatrix = glm::scale(suzanneModelMatrix, glm::vec3(suzanneScale, suzanneScale, suzanneScale));
            suzanneModelMatrix = glm::translate(suzanneModelMatrix, glm::vec3(0.0f, -2.5f, 0.0f));
            glm::mat4 suzanneMVP = projection * view * suzanneModelMatrix;            
            glUniformMatrix4fv(locMVP, 1, GL_FALSE, &suzanneMVP[0][0]);
            textSuzanne.use();
            suzanne.draw();
		}      

        glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
        modelShader.use(); 
        textGround.use();
        textGround.enableMipmap();
        ground.draw(GL_TRIANGLES, 6);

        //For each group apply transform and draw
        for (int i = 0; i < N_GROUPS; i++)
        {
            glm::vec3 treePos = glm::vec3(treeTransform[i][3][0], treeTransform[i][3][1], treeTransform[i][3][2]);
            glm::vec3 camToTree = glm::normalize(treePos - camPosition);
            float dist = glm::length(treePos - camPosition);
            if (dist > 25.0f) {
                glm::mat4 billBoard = glm::mat4(1.0f);
                const float billboardScale = 3.15f;
                billBoard = glm::scale(billBoard, glm::vec3(billboardScale * 0.96, billboardScale, 1));
                mvp = view * treeTransform[i] * billBoard;

                float sX = glm::length(glm::vec3(mvp[0]));
                float sZ = glm::length(glm::vec3(mvp[2]));

                mvp[0][0] = sX;
                mvp[0][1] = 0.0f;
                mvp[0][2] = 0.0f;
                mvp[2][0] = 0.0f;
                mvp[2][1] = 0.0f;
                mvp[2][2] = sZ;

                mvp = projection * mvp;

                glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
                treeBillboard.use();
                billboard.draw(GL_TRIANGLES, 6);
            }
            else {
                mvp = projection * view * treeTransform[i];
                glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
                textTree.use();
                tree.draw();
            }
            
			mvp = projection * view * rockTransform[i];
			glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
            textRock.use();
			rock.draw();

            mvp = projection * view * shroomTransform[i];
			glUniformMatrix4fv(locMVP, 1, GL_FALSE, &mvp[0][0]);
            textShroom.use();
			shroom.draw();
		}

        //Disable face culling
        glDisable(GL_CULL_FACE);

        grassShader.use();
        textGrass.use();
        mvp = projection * view;
        glUniformMatrix4fv(locMVPGrass, 1, GL_FALSE, &mvp[0][0]);
		glUniform1f(locTimeGrass, time / 1000.0f);


        for(BasicShapeMultipleArrays* grass : grasses)
		{
			grass->draw(GL_TRIANGLES, 18);
		}

        glDepthMask(GL_FALSE);
        skyBoxShader.use();
        glUniformMatrix4fv(locMVPSkyBox, 1, GL_FALSE, &mvp[0][0]);
        textSkyBox.use();
        skyBox.draw(GL_TRIANGLES, 36);
        glDepthMask(GL_TRUE);


        w.swap();
        w.pollEvent();
        isRunning = !w.shouldClose() && !w.getKeyPress(Window::Key::ESC);
    }
    return 0;
}



void checkGLError(int line)
{
    GLenum error;
    while ( ( error = glGetError() ) != GL_NO_ERROR )
    {
        std::cerr << "Line "<< line << ": ";
        switch ( error )
        {
        case GL_INVALID_ENUM:
            std::cerr << "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            std::cerr << "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            std::cerr << "GL_INVALID_OPERATION";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            std::cerr << "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            std::cerr << "GL_OUT_OF_MEMORY";
            break;
        case GL_STACK_UNDERFLOW:
            std::cerr << "GL_STACK_UNDERFLOW";
            break;
        case GL_STACK_OVERFLOW:
            std::cerr << "GL_STACK_OVERFLOW";
            break;
        default:
            std::cerr << "Unknown gl error occured!";
            break;
        }
        std::cerr << std::endl;
    }    
}

void printGLInfo()
{
    std::cout << "OpenGL info:" << std::endl;
    std::cout << "    Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "    Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "    Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "    Shading version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

std::string readFile(const char* path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void genTransformForGroup(GLint N_ROWS, glm::mat4* groupsTransform, glm::mat4* treeTransform, glm::mat4* rockTransform, glm::mat4* shroomTransform) {

    for (int i = 0; i < N_ROWS; i++) {
        for (int j = 0; j < N_ROWS; j++) {
            int groupId = i * N_ROWS + j;
            float x, z;
            getGroupRandomPos(groupId, N_ROWS, x, z);
            groupsTransform[groupId] = glm::translate(glm::mat4(1.0f), glm::vec3(x, 0, z));

            float randScale = 0.8f + rand01() * 0.5f;
            groupsTransform[groupId] = glm::scale(groupsTransform[groupId], glm::vec3(randScale));

            float randRot = rand01() * 2 * 3.14159f;
            groupsTransform[groupId] = glm::rotate(groupsTransform[groupId], randRot, glm::vec3(0, 1, 0));

            treeTransform[groupId] = groupsTransform[groupId];
            float randScaleTree = 0.7f + rand01() * 0.6f;
            treeTransform[groupId] = glm::scale(treeTransform[groupId], glm::vec3(randScaleTree * 1));

            rockTransform[groupId] = groupsTransform[groupId];
            float angleRock = rand01() * 2 * 3.14159f;
            float circleRadius = 2.0f + rand01();
            float randScaleRock = 0.2f + rand01() * 0.8f;
            rockTransform[groupId] = glm::translate(rockTransform[groupId], glm::vec3(cos(angleRock) * circleRadius, 0.0f, sin(angleRock) * circleRadius));
            rockTransform[groupId] = glm::rotate(rockTransform[groupId], angleRock, glm::vec3(0, 1, 0));
            rockTransform[groupId] = glm::scale(rockTransform[groupId], glm::vec3(randScaleRock));


            shroomTransform[groupId] = groupsTransform[groupId];
            glm::vec3 shroomPos = glm::vec3(0.3f, 0.0f, 0.3f);
            shroomTransform[groupId] = glm::translate(shroomTransform[groupId], shroomPos);
            shroomTransform[groupId] = glm::scale(shroomTransform[groupId], glm::vec3(0.1f));

        }
    }
}

void updateCameraWithKeyboard(Window& w, float speed, glm::vec3& camPosition, glm::vec2& camOrientation, Camera& camera) {
    GLfloat yaw = camOrientation.x;
    GLfloat pitch = camOrientation.y;

    glm::vec3 front = glm::normalize(glm::vec3(sin(yaw), 0, -cos(yaw)));
    glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));


    if (w.getKeyHold(Window::Key::W))
    {
        camPosition += front * speed;
    }
    if (w.getKeyHold(Window::Key::S))
    {
        camPosition -= front * speed;
    }
    if (w.getKeyHold(Window::Key::D))
    {
        camPosition += right * speed;
    }
    if (w.getKeyHold(Window::Key::A))
    {
        camPosition -= right * speed;
    }
    if (w.getMouseScrollDirection()!=0){
        camera.toggleMode();
    }

    int xMouseMove = 0;
    int yMouseMove = 0;
    w.getMouseMotion(xMouseMove, yMouseMove);

    camOrientation.x += xMouseMove * 0.003f;
    camOrientation.y += yMouseMove * 0.003f;


    // Clamp pitch
    if (camOrientation.y > 1.5f)
        camOrientation.y = 1.5f;
    if (camOrientation.y < -1.5f)
        camOrientation.y = -1.5f;
    if (camera.getMode() == CameraMode::ThirdPerson && camOrientation.y < -0.15f) 
        camOrientation.y = -0.15f;
	
}

void genGrass(std::vector<BasicShapeMultipleArrays*>& grasses, int N_GRASS, const GLfloat grassPosition[],
    const GLint posSize, const GLfloat grassTexCoords[], const GLint textSize) {

    for (int i = 0; i < N_GRASS; i++) {

        int atlasIndex = i % 3;

        std::vector<GLfloat> newGrassTexCoords(grassTexCoords, grassTexCoords + textSize);
        for (int j = 0; j < textSize; j += 2) {
            newGrassTexCoords[j] = newGrassTexCoords[j] * 0.33f + atlasIndex * 0.33f;
        }

        GLfloat randX = rand01() * 60.0f - 30.0f;
        GLfloat randZ = rand01() * 60.0f - 30.0f;

        std::vector<GLfloat> newGrassPosition(grassPosition, grassPosition + posSize);
        for (int j = 0; j < posSize; j += 3) {
            newGrassPosition[j] = newGrassPosition[j] + randX;
            newGrassPosition[j + 2] = newGrassPosition[j + 2] + randZ;
        }
       
        grasses.push_back(new BasicShapeMultipleArrays(newGrassPosition.data(), posSize * sizeof(GLfloat),
			newGrassTexCoords.data(), textSize * sizeof(GLfloat)));
        grasses[i]->enablePosAttribute(0, 3, 0, 0);
        grasses[i]->enableColorAttribute(8, 2, 0, 0);
    }
}

