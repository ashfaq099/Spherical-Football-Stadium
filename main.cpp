
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "camera.h"
#include "basic_camera.h"
#include "pointLight.h"
#include "directionLight.h"
#include "sphere.h"
#include "spotLight.h"
#include "cube.h"
#include "stb_image.h"
#include "cylinder.h"

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model, float r, float g, float b);
void stadium(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether);
void drawFloodlight(unsigned int& cubeVAO, Shader& lightingShader, glm::vec3 position);
unsigned int Texture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax);


const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


float rotateAngle_X = 0.0;
float rotateAngle_Y = 0.0;
float rotateAngle_Z = 0.0;
float rotateAxis_X = 0.0;
float rotateAxis_Y = 0.0;
float rotateAxis_Z = 1.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float translate_Z = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;
float scale_Z = 1.0;
float run_speed = 0.004f;
float angle_ball = 0.0f;
float ball_z = 5.0f;
float ball_x = 0.0f;
float ball_y = 0.0f;
bool ball_shoot = false;
float bz = 0.0f;
float bar_x = 0.0f;


float gun_x=0.0f;
float gun_y=0.7f;
float balloon_x=1.5f;
float balloon_y = 1.2f;

bool first_block = true;
bool balloon = true;
bool gameOver = false;

int difficult = 0;


float camera_z = 0.0f;
Camera camera(glm::vec3(0.0f, 1.0f, -6.5f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
float inc = 0.1f;

int score = 0;
bool start = true;
float slope = 0.0f;
int ball_count = 0;

float eyeX = 0.0, eyeY = 10.0, eyeZ = 1.0;
float lookAtX = 0.0, lookAtY = 10.0, lookAtZ = 0.0;
glm::vec3 V = glm::vec3(0.0f, 1.0f, 0.0f);
BasicCamera basic_camera(eyeX, eyeY, eyeZ, lookAtX, lookAtY, lookAtZ, V);
SpotLight spotlight(
    0.0f,1.0f,-3.0f,
    0.0f, -1.0f, 0.0f,
    .0f, .0f, .0f,
    .0f, .0f, .0f,
    0.0f, 0.0f, 0.0f,
    30.0f,
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);

DirectionLight directlight(
    0.0f, 1.0f, 0.0f,
    .0f, .0f, .0f,
    .0f, .0f, .0f,
    0.0f, 0.0f, 0.0f,
    1.0f,   //k_c
    0.09f,  //k_l
    0.032f //k_q
);

glm::vec3 pointLightPositions[] = {
    glm::vec3(-8.0f, 10.0f, -6.5f),  // back left
    glm::vec3(-8.0f, 10.0f, 23.5f),  // front left
    glm::vec3(8.0f, 10.0f, -6.5f),   // back right
    glm::vec3(8.0f, 10.0f, 23.5f)    // front right
};
PointLight pointlight1(
    pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z,
    0.2f, 0.2f, 0.2f,      // increased ambient
    1.5f, 1.5f, 1.5f,      // increased diffuse
    2.0f, 2.0f, 2.0f,      // increased specular
    1.0f,   // k_c
    0.045f, // reduced linear attenuation
    0.0075f,// reduced quadratic attenuation
    1
);

PointLight pointlight2(
    pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z,
    0.2f, 0.2f, 0.2f,
    1.5f, 1.5f, 1.5f,
    2.0f, 2.0f, 2.0f,
    1.0f,
    0.045f,
    0.0075f,
    2
);

PointLight pointlight3(
    pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z,
    0.2f, 0.2f, 0.2f,
    1.5f, 1.5f, 1.5f,
    2.0f, 2.0f, 2.0f,
    1.0f,
    0.045f,
    0.0075f,
    3
);

PointLight pointlight4(
    pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z,
    0.2f, 0.2f, 0.2f,
    1.5f, 1.5f, 1.5f,
    2.0f, 2.0f, 2.0f,
    1.0f,
    0.045f,
    0.0075f,
    4
);

bool pointLightOn = true;
bool directionLighton = true;
bool spotlighton = true;
bool ambientToggle = true;
bool diffuseToggle = true;
bool specularToggle = true;
bool shoot = false;
float bullet_z = -5.2f;


float deltaTime = 0.0f;    
float lastFrame = 0.0f;
int serial = 0;

int main()
{
 
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

   
   
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Football Stadium", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
  
    glfwSetScrollCallback(window, scroll_callback);

    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    
    glEnable(GL_DEPTH_TEST);

   
  
    Shader lightingShader("vertexShaderForPhongShading.vs", "fragmentShaderForPhongShading.fs");
    
    Shader ourShader("vertexShader.vs", "fragmentShader.fs");

   
    

    float cube_vertices[] = {
        // positions      // normals
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,

        1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

        0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,

        0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f
    };
    unsigned int cube_indices[] = {
        0, 3, 2,
        2, 1, 0,

        4, 5, 7,
        7, 6, 4,

        8, 9, 10,
        10, 11, 8,

        12, 13, 14,
        14, 15, 12,

        16, 17, 18,
        18, 19, 16,

        20, 21, 22,
        22, 23, 20
    };

    unsigned int cubeVAO, cubeVBO, cubeEBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glGenBuffers(1, &cubeEBO);

    glBindVertexArray(cubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);


    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

   
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeEBO);
 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Sphere sphere = Sphere();

   // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    string laughEmoPath = "football.png";
    unsigned int laughEmoji = Texture(laughEmoPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);

    Shader lightingShaderWithTexture("vertexShaderForPhongShadingWithTexture.vs", "fragmentShaderForPhongShadingWithTexture.fs");

    string diffuseMapPath = "field.jpg";
    string specularMapPath = "field.jpg";

    unsigned int diffMap = Texture(diffuseMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap = Texture(specularMapPath.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube field = Cube(diffMap, specMap, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath2 = "seat.png";
    string specularMapPath2 = "seat.png";

    unsigned int diffMap2 = Texture(diffuseMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap2 = Texture(specularMapPath2.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube seat = Cube(diffMap2, specMap2, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath3 = "score.jpg";
    string specularMapPath3 = "score.jpg";

    unsigned int diffMap3 = Texture(diffuseMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap3 = Texture(specularMapPath3.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube scoreB = Cube(diffMap3, specMap3, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);


    string diffuseMapPath4 = "GameOver.jpg";
    string specularMapPath4 = "GameOver.jpg";

    unsigned int diffMap4 = Texture(diffuseMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    unsigned int specMap4 = Texture(specularMapPath4.c_str(), GL_REPEAT, GL_REPEAT, GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR);
    Cube GameOver = Cube(diffMap4, specMap4, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f);

    Cylinder bar = Cylinder();
    bar.setRadius(0.1);
    bar.diffuse = glm::vec3(1.0, 1.0, 1.0);
    bar.ambient = glm::vec3(1.0, 1.0, 1.0);
    bar.specular = glm::vec3(1.0, 1.0, 1.0);


    Sphere ball = Sphere();
 
    camera.Position = glm::vec3(2.0, 3.0, 0.0);

    int count = 0;
    while (!glfwWindowShouldClose(window))
    {
        
       
  
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        
    
        processInput(window);

     
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        

        
        lightingShader.use();
        lightingShader.setVec3("viewPos", camera.Position);

        // point light 1
        pointlight1.setUpPointLight(lightingShader);
        // point light 2
        pointlight2.setUpPointLight(lightingShader);
        // point light 3
        pointlight3.setUpPointLight(lightingShader);
        // point light 4
        pointlight4.setUpPointLight(lightingShader);

        directlight.setUpDirectionLight(lightingShader);

        spotlight.setUpSpotLight(lightingShader);

        
        lightingShader.use();

       
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        
        lightingShader.setMat4("projection", projection);

        
        glm::mat4 view = camera.GetViewMatrix();
      
        lightingShader.setMat4("view", view);

      
        glm::mat4 identityMatrix = glm::mat4(1.0f); 
        glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, translate_Z));
        rotateXMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_X), glm::vec3(1.0f, 0.0f, 0.0f));
        rotateYMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Y), glm::vec3(0.0f, 1.0f, 0.0f));
        rotateZMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle_Z), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, scale_Z));
        model = translateMatrix * rotateXMatrix * rotateYMatrix * rotateZMatrix * scaleMatrix;
        lightingShader.setMat4("model", model);
        stadium(cubeVAO, lightingShader, model);
       
        //bar
        glm::mat4 bar1 = glm::mat4(1.0f);
        bar1 = glm::translate(model, glm::vec3(0.4f, -0.2f, 0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
        bar1 = bar1 * scaleMatrix;
        bar.drawCylinder(lightingShader, bar1, 1.0,1.0,1.0);

        bar1 = glm::mat4(1.0f);
        bar1 = glm::translate(model, glm::vec3(-0.4f, -0.2f, 0.4f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
        bar1 = bar1 * scaleMatrix;
        bar.drawCylinder(lightingShader, bar1, 1.0, 1.0, 1.0);

        bar1 = glm::mat4(1.0f);
        bar1 = glm::translate(model, glm::vec3(0.0f, 0.8f, 0.4f));
        glm::mat4 bar1_r = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.4f, 0.1f));
        bar1 = bar1 * bar1_r * scaleMatrix;
        bar.drawCylinder(lightingShader, bar1, 1.0, 1.0, 1.0);

        if (difficult == 1)
            bar_x += (0.1 * inc);
        else if (difficult == 2)
            bar_x += (0.2 * inc);
        else if(difficult == 3)
            bar_x += (0.3 * inc);

        if (bar_x - 0.4 <= -2.5f)
            inc = 0.1f;
        if (bar_x + 0.4 >= 2.5f)
            inc = -0.1f;

        glm::mat4 bar2 = glm::mat4(1.0f);
        bar2 = glm::translate(model, glm::vec3(0.4f+bar_x, -0.2f, 9.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
        bar2 = bar2 * scaleMatrix;
        bar.drawCylinder(lightingShader, bar2, 1.0, 1.0, 1.0);

        bar2 = glm::mat4(1.0f);
        bar2 = glm::translate(model, glm::vec3(-0.4f + bar_x, -0.2f, 9.6f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.0f, 0.1f));
        bar2 = bar2 * scaleMatrix;
        bar.drawCylinder(lightingShader, bar2, 1.0, 1.0, 1.0);

        bar2 = glm::mat4(1.0f);
        bar2 = glm::translate(model, glm::vec3(0.0f + bar_x, 0.8f, 9.6f));
        glm::mat4 bar2_r = glm::rotate(identityMatrix, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.4f, 0.1f));
        bar2 = bar2 * bar2_r * scaleMatrix;
        bar.drawCylinder(lightingShader, bar2, 1.0, 1.0, 1.0);


        //scoreboard
        glm::mat4 modelForScore = identityMatrix;
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25f, 2.0f, 10.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, 1.5, 0.2));
        modelForScore = modelForScore * translateMatrix  * scaleMatrix;
        drawCube(cubeVAO, lightingShader, modelForScore, 0.9, 0.8, 0.9);

        glm::mat4 stand = glm::mat4(1.0f);
        stand = glm::translate(model, glm::vec3(1.4f , -1.0f, 10.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.0f, 0.1f));
        stand = stand * scaleMatrix;
        bar.drawCylinder(lightingShader, stand, 1.0, 1.0, 1.0);

        stand = glm::mat4(1.0f);
        stand = glm::translate(model, glm::vec3(-1.4f, -1.0f, 10.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 4.0f, 0.1f));
        stand = stand * scaleMatrix;
        bar.drawCylinder(lightingShader, stand, 1.0, 1.0, 1.0);

        stand = glm::mat4(1.0f);
        stand = glm::translate(model, glm::vec3(0.0f, 2.8f, 10.1f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 1.4f, 0.1f));
        stand = stand * bar2_r * scaleMatrix;
        bar.drawCylinder(lightingShader, stand, 1.0, 1.0, 1.0);

 
        float sbx = 0.0f;
        for (int i = 0; i < score; i++)
        {
            glm::mat4 modelForScore = identityMatrix;
            translateMatrix = glm::translate(model, glm::vec3(0.8f-sbx, 2.6f, 10.0f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
            modelForScore = modelForScore * translateMatrix * scaleMatrix;
            ball.drawSphere(lightingShader, laughEmoji, modelForScore);
            sbx += 0.2f;
        }
        glm::mat4 modelForBall = identityMatrix;
        translateMatrix = glm::translate(model, glm::vec3(ball_x, 0.36f, ball_z + bz));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.1f, 0.1f, 0.1f));
        modelForBall = modelForBall * translateMatrix * scaleMatrix;
        sphere.drawSphere(lightingShaderWithTexture, laughEmoji, modelForBall);


        //ball shoot

        if (ball_shoot)
        {
            bz += 0.03f;
            ball_x = slope * bz;

           
        }

        if (ball_z + bz >= 10.0)
        {
            start = false;
            if (ball_x > -0.4f + bar_x && ball_x < 0.4 + bar_x)
            {
                if (serial == ball_count)
                {
                   if(score<9)
                        score++;
                    serial--;
                    
                }
                    
            }
            else
            {
                if (serial == ball_count)
                {
                    if(score>0)
                        score--;
                    serial--;

                }
            }
            ball_shoot = false;
            ball_x = 0.0f;
            bz = 0.0f;
            printf("%d\n", score);
        }

       

        glm::mat4 rotArrow = glm::rotate(identityMatrix, glm::radians(angle_ball), glm::vec3(0.0f, 1.0f, 0.0f));
        glm::mat4 modelForArrow = identityMatrix;
        translateMatrix = glm::translate(model, glm::vec3( -0.02, 0.36f, 5.0));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.05f, 0.01f, 0.5f));
        modelForArrow = modelForArrow * translateMatrix * rotArrow * scaleMatrix;
        drawCube(cubeVAO, lightingShader, modelForArrow, 1.0, 1.0, 1.0);


      
        ourShader.use();
        ourShader.setMat4("projection", projection);
        ourShader.setMat4("view", view);
        float cr, cg, cb;
        if (pointLightOn)
        {
            cr = 0.8f;
            cg = 0.8f;
            cb = 0.8f;
        }
        else
        {
            cr = 0.0f;
            cg = 0.0f;
            cb = 0.0f;
        }

        

glBindVertexArray(lightCubeVAO);
for (unsigned int i = 0; i < 4; i++) {
    drawFloodlight(cubeVAO, lightingShader, pointLightPositions[i]);
}

        glBindVertexArray(lightCubeVAO);
        for (unsigned int i = 0; i < 4; i++)
        {
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPositions[i]);
            model = glm::scale(model, glm::vec3(0.4f)); // Make it a smaller cube
            ourShader.setMat4("model", model);
            ourShader.setVec3("color", glm::vec3(cr, cg, cb));
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(lightCubeVAO);
           
         
        }


        lightingShaderWithTexture.use();
        lightingShaderWithTexture.setVec3("viewPos", camera.Position);
        lightingShaderWithTexture.setMat4("projection", projection);
        lightingShaderWithTexture.setMat4("view", view);

        lightingShaderWithTexture.use();
        // point light 1
        pointlight1.setUpPointLight(lightingShaderWithTexture);
        // point light 2
        pointlight2.setUpPointLight(lightingShaderWithTexture);
        // point light 3
        pointlight3.setUpPointLight(lightingShaderWithTexture);
        // point light 4
        pointlight4.setUpPointLight(lightingShaderWithTexture);



        //field
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-2.5f, 0.1f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(5.0f, 0.2f, 10.0f));
        glm::mat4 modelMatrixForfield = translateMatrix * scaleMatrix;
        field.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForfield);
        
       
        //scoreboard
        translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25f, 2.0f, 9.99f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, 1.5, 0.2));
        glm::mat4 modelMatrixForScore = translateMatrix * scaleMatrix;
        scoreB.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForScore);

        //gameOver

        if (!start && score == 0)
            gameOver = true;

        if (gameOver && !start)
        {
            translateMatrix = glm::translate(identityMatrix, glm::vec3(-1.25f, 2.0f, 9.98f));
            scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.5, 1.5, 0.2));
            glm::mat4 modelMatrixForScore = translateMatrix * scaleMatrix;
            GameOver.drawCubeWithTexture(lightingShaderWithTexture, modelMatrixForScore);
        }

   

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

  
   
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &cubeVBO);
    glDeleteBuffers(1, &cubeEBO);

    

    glfwTerminate();
    return 0;
}

void drawCube(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 model = glm::mat4(1.0f), float r = 1.0f, float g = 1.0f, float b = 1.0f)
{
    lightingShader.use();
    lightingShader.setVec3("material.ambient", glm::vec3(r, g, b));
    lightingShader.setVec3("material.diffuse", glm::vec3(r, g, b));
    lightingShader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    lightingShader.setFloat("material.shininess", 22.0f);
    lightingShader.setMat4("model", model);

    glBindVertexArray(cubeVAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}



void stadium(unsigned int& cubeVAO, Shader& lightingShader, glm::mat4 alTogether)
{
    
    int numSegments = 200; 
    float angleStep = 360.0f / numSegments;
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 translateMatrix, rotateXMatrix, rotateYMatrix, rotateZMatrix, scaleMatrix, model;

    // Base (field)
    translateMatrix = glm::translate(identityMatrix, glm::vec3(-17.0f, 0.09f, -7.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(30.0, 0.2, 30.0));
    model = translateMatrix * scaleMatrix;
  
    drawCube(cubeVAO, lightingShader, model, 0.3569f, 0.5686f, 0.2314f);
    // Draw circular seating
    for (int i = 0; i < numSegments; i++) {
        float angle = glm::radians(i * angleStep);
      
        float baseX = 6.0f * cos(angle)+0.2f; 
        float baseZ = 15.0f * sin(angle) +8.5f;  

        // First row (outermost)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(baseX, 1.4f, baseZ));
        rotateYMatrix = glm::rotate(identityMatrix, angle, glm::vec3(0.0f, 1.0f, 0.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(1.0, 0.4, 2.0));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5686f, 0.6745f, 0.5608f);

        // Second row (moving inward and down)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(baseX * 0.95f, 1.0f, baseZ * 0.95f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.9, 0.4, 1.8));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.6196f, 0.8745f, 0.6118f);

        // Third row
        translateMatrix = glm::translate(identityMatrix, glm::vec3(baseX * 0.90f, 0.6f, baseZ * 0.90f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.8, 0.4, 1.6));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.5569f, 0.6392f, 0.6510f);

        // Fourth row (innermost, lowest)
        translateMatrix = glm::translate(identityMatrix, glm::vec3(baseX * 0.85f, 0.2f, baseZ * 0.85f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.7, 0.4, 1.4));
        model = translateMatrix * rotateYMatrix * scaleMatrix;
        drawCube(cubeVAO, lightingShader, model, 0.3843f, 0.5098f, 0.3647f);
    }
}
void drawFloodlight(unsigned int& cubeVAO, Shader& lightingShader, glm::vec3 position) {
    glm::mat4 identityMatrix = glm::mat4(1.0f);
    glm::mat4 model, translateMatrix, rotateMatrix, scaleMatrix;
    
    translateMatrix = glm::translate(identityMatrix, glm::vec3(position.x, 0.0f, position.z));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(0.5f, position.y, 0.5f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.5f, 0.5f, 0.5f);

    translateMatrix = glm::translate(identityMatrix, glm::vec3(position.x - 1.0f, position.y - 1.0f, position.z - 1.0f));
    scaleMatrix = glm::scale(identityMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
    model = translateMatrix * scaleMatrix;
    drawCube(cubeVAO, lightingShader, model, 0.7f, 0.7f, 0.7f);
    
}


void processInput(GLFWwindow* window)
{
   
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

  
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);  // Changed from FORWARD
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);   // Changed from BACKWARD
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);     // Changed from LEFT
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);      // Changed from RIGHT

    
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, deltaTime);

  
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(P_UP, deltaTime);    // Pitch Up
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(P_DOWN, deltaTime);  // Pitch Down
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(Y_LEFT, deltaTime);  // Yaw Left
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(Y_RIGHT, deltaTime); // Yaw Right
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(R_LEFT, deltaTime);  // Roll Left
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(R_RIGHT, deltaTime); // Roll Right

    
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        if (!ball_shoot)
            angle_ball += 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (!ball_shoot)
            angle_ball -= 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (!gameOver) {
            ball_count++;
            serial = ball_count;
            ball_shoot = true;
            slope = tanf(3.1416 * angle_ball / 180.0);
        }
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        start = true;
        gameOver = false;
    }

    
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
        difficult = 1;
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
        difficult = 2;
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        difficult = 3;
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{   
    if (key == GLFW_KEY_1 && action == GLFW_PRESS)
    {
        if (directionLighton)
        {
            directlight.turnOff();
            directionLighton = !directionLighton;
        }
        else
        {
            directlight.turnOn();
            directionLighton = !directionLighton;
        }
    }
    else if (key == GLFW_KEY_2 && action == GLFW_PRESS)
    {
        if (pointLightOn)
        {
            pointlight1.turnOff();
            pointlight2.turnOff();
            pointlight3.turnOff();
            pointlight4.turnOff();
            pointLightOn = !pointLightOn;
        }
        else
        {
            pointlight1.turnOn();
            pointlight2.turnOn();
            pointlight3.turnOn();
            pointlight4.turnOn();
            pointLightOn = !pointLightOn;
        }
    }
    else if (key == GLFW_KEY_3 && action == GLFW_PRESS)
    {
        if (spotlighton)
        {
            spotlight.turnOff();
            spotlighton = !spotlighton;
        }
        else
        {
            spotlight.turnOn();
            spotlighton = !spotlighton;
        }
    }
    else if (key == GLFW_KEY_4 && action == GLFW_PRESS)
    {
        if (ambientToggle)
        {
            pointlight1.turnAmbientOff();
            pointlight2.turnAmbientOff();
            pointlight3.turnAmbientOff();
            pointlight4.turnAmbientOff();
            directlight.turnAmbientOff();
            spotlight.turnAmbientOff();
            ambientToggle = !ambientToggle;
        }
        else
        {
            pointlight1.turnAmbientOn();
            pointlight2.turnAmbientOn();
            pointlight3.turnAmbientOn();
            pointlight4.turnAmbientOn();
            directlight.turnAmbientOn();
            spotlight.turnAmbientOn();
            ambientToggle = !ambientToggle;
        }
    }
    else if (key == GLFW_KEY_5 && action == GLFW_PRESS)
    {
        if (diffuseToggle)
        {
            pointlight1.turnDiffuseOff();
            pointlight2.turnDiffuseOff();
            pointlight3.turnDiffuseOff();
            pointlight4.turnDiffuseOff();
            directlight.turnDiffuseOff();
            spotlight.turnDiffuseOff();
            diffuseToggle = !diffuseToggle;
        }
        else
        {
            pointlight1.turnDiffuseOn();
            pointlight2.turnDiffuseOn();
            pointlight3.turnDiffuseOn();
            pointlight4.turnDiffuseOn();
            directlight.turnDiffuseOn();
            spotlight.turnDiffuseOn();
            diffuseToggle = !diffuseToggle;
        }
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
    {
        if (specularToggle)
        {
            pointlight1.turnSpecularOff();
            pointlight2.turnSpecularOff();
            pointlight3.turnSpecularOff();
            pointlight4.turnSpecularOff();
            directlight.turnSpecularOff();
            spotlight.turnSpecularOff();
            specularToggle = !specularToggle;
        }
        else
        {
            pointlight1.turnSpecularOn();
            pointlight2.turnSpecularOn();
            pointlight3.turnSpecularOn();
            pointlight4.turnSpecularOn();
            directlight.turnSpecularOn();
            spotlight.turnSpecularOn();
            specularToggle = !specularToggle;
        }
    }
    else if (key == GLFW_KEY_6 && action == GLFW_PRESS)
        difficult = 0;

}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

unsigned int Texture(char const* path, GLenum textureWrappingModeS, GLenum textureWrappingModeT, GLenum textureFilteringModeMin, GLenum textureFilteringModeMax)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureWrappingModeS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureWrappingModeT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilteringModeMin);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilteringModeMax);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}