#include "Assignment3.h"
#include "GL\glew.h"

#include "Utility.h"
#include "Material.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"
#include "LoadTGA.h"

Assignment3::Assignment3() :
LSPEED(10)
{

}

Assignment3::~Assignment3()
{

}


void Assignment3::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //Enable depth buffer and depth testing
    glEnable(GL_DEPTH_TEST);

    //Enable back face culling
    glEnable(GL_CULL_FACE);


    //Default to fill mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // Generate a default VAO for now
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    //Shader
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

    //Lighting
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
    m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
    m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
    m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
    m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
    m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
    m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
    m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
    m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
    m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
    m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
    m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
    m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
    m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDiection");
    m_parameters[U_LIGHT0_cosCutOff] = glGetUniformLocation(m_programID, "lights[0].cosCutOff");
    m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
    m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

    m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
    m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
    m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
    m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
    m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
    m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
    m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
    m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
    m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDiection");
    m_parameters[U_LIGHT1_cosCutOff] = glGetUniformLocation(m_programID, "lights[1].cosCutOff");
    m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
    m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");

    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

    //Texture
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

    // Get a handle for our "textColor" uniform
    m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
    m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

    glUseProgram(m_programID);



    //Light Object
    light[0].type = Light::LIGHT_POINT;
    light[0].position.Set(0, 95, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 2.f;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
    light[0].cosCutOff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 3.f;
    light[0].spotDirection.Set(0.f, -1.f, 0.f);

    light[1].type = Light::LIGHT_SPOT;
    light[1].position.Set(160, 86, 155);
    light[1].color.Set(1, 1, 1);
    light[1].power = 1.f;
    light[1].kC = 1.f;
    light[1].kL = 0.01f;
    light[1].kQ = 0.001f;
    light[1].cosCutOff = cos(Math::DegreeToRadian(45));
    light[1].cosInner = cos(Math::DegreeToRadian(30));
    light[1].exponent = 3.f;
    light[1].spotDirection.Set(1.f, 1.f, 0.f);


    // Make sure you pass uniform parameters after glUseProgram

    glUniform1i(m_parameters[U_NUMLIGHTS], 2);
    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_cosCutOff], light[0].cosCutOff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

    glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
    glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
    glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
    glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
    glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
    glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
    glUniform1f(m_parameters[U_LIGHT1_cosCutOff], light[1].cosCutOff);
    glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
    glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //variable to rotate geometry


    //Initialize camera settings
    camera.Init(Vector3(0, 50, 1), Vector3(0, 50, 0), Vector3(0, 1, 0));


    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", (1, 1, 1), 18, 36);

    meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 10, 10);
    meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

    meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 10, 10);
    meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

    meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 10, 10);
    meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

    meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 10, 10);
    meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

    meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 10, 10);
    meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

    meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 10, 10);
    meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

    meshList[GEO_BATHBOTTOM] = MeshBuilder::GenerateQuad("bathbottom", Color(1, 1, 1), 10, 10);
    meshList[GEO_BATHBOTTOM]->textureID = LoadTGA("Image//bathbottom.tga");

    meshList[GEO_BATHFRONT] = MeshBuilder::GenerateQuad("bathfront", Color(1, 1, 1), 10, 10);
    meshList[GEO_BATHFRONT]->textureID = LoadTGA("Image//bathwall.tga");

    meshList[GEO_BATHRIGHT] = MeshBuilder::GenerateQuad("bathright", Color(1, 1, 1), 10, 10);
    meshList[GEO_BATHRIGHT]->textureID = LoadTGA("Image//bathwall.tga");

    meshList[GEO_BATHLEFT] = MeshBuilder::GenerateQuad("bathleft", Color(1, 1, 1), 10, 10);
    meshList[GEO_BATHLEFT]->textureID = LoadTGA("Image//bathwall.tga");

    meshList[GEO_BATHBACK] = MeshBuilder::GenerateQuad("bathback", Color(1, 1, 1), 10, 10);
    meshList[GEO_BATHBACK]->textureID = LoadTGA("Image//bathwall.tga");

    meshList[GEO_BATHTOP] = MeshBuilder::GenerateQuad("bathback", Color(1, 1, 1), 10, 10);

    meshList[GEO_LAMP] = MeshBuilder::GenerateOBJ("Lamp", "OBJ//lamp.obj");
    meshList[GEO_LAMP]->textureID = LoadTGA("Image//coke.tga");
    meshList[GEO_LAMP]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_LAMP]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_LAMP]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_LAMP]->material.kShininess = 0.78125;

    meshList[GEO_DESK] = MeshBuilder::GenerateOBJ("DESK", "OBJ//WorkDesk.obj");
    meshList[GEO_DESK]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_DESK]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_DESK]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_DESK]->material.kShininess = 0.78125;

    meshList[GEO_CAN] = MeshBuilder::GenerateOBJ("Can", "OBJ//coke.obj");
    meshList[GEO_CAN]->textureID = LoadTGA("Image//coke.tga");
    meshList[GEO_CAN]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_CAN]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_CAN]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_CAN]->material.kShininess = 0.78125;

    meshList[GEO_BED] = MeshBuilder::GenerateOBJ("Bed", "OBJ//bed.obj");
    meshList[GEO_BED]->textureID = LoadTGA("Image//bed.tga");
    meshList[GEO_BED]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_BED]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_BED]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_BED]->material.kShininess = 0.78125;

    meshList[GEO_MATTRESS] = MeshBuilder::GenerateOBJ("Mattress", "OBJ//mattress.obj");
    meshList[GEO_MATTRESS]->textureID = LoadTGA("Image//mattress.tga");
    meshList[GEO_MATTRESS]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_MATTRESS]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_MATTRESS]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_MATTRESS]->material.kShininess = 0.78125;

    meshList[GEO_DESKLAMP] = MeshBuilder::GenerateOBJ("DOOR", "OBJ//desklamp.obj");
    meshList[GEO_DESKLAMP]->textureID = LoadTGA("Image//metal.tga");
    meshList[GEO_DESKLAMP]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_DESKLAMP]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_DESKLAMP]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_DESKLAMP]->material.kShininess = 0.78125;

    meshList[GEO_DOORFRAME] = MeshBuilder::GenerateOBJ("DOORFRAME", "OBJ//doorFrame.obj");
    meshList[GEO_DOORFRAME]->textureID = LoadTGA("Image//doorFrame.tga");
    meshList[GEO_DOORFRAME]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_DOORFRAME]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_DOORFRAME]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_DOORFRAME]->material.kShininess = 0.78125;

    meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("Door", "OBJ//door.obj");
    meshList[GEO_DOOR]->textureID = LoadTGA("Image//door.tga");
    meshList[GEO_DOOR]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_DOOR]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_DOOR]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_DOOR]->material.kShininess = 0.78125;

    meshList[GEO_TOILET] = MeshBuilder::GenerateOBJ("Toilet", "OBJ//toilet.obj");
    meshList[GEO_TOILET]->textureID = LoadTGA("Image//toilet.tga");
    meshList[GEO_TOILET]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_TOILET]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_TOILET]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_TOILET]->material.kShininess = 0.78125;

    meshList[GEO_TOILETWATER] = MeshBuilder::GenerateOBJ("ToiletWater", "OBJ//toiletWater.obj");
    meshList[GEO_TOILETWATER]->textureID = LoadTGA("Image//water.tga");
    meshList[GEO_TOILETWATER]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_TOILETWATER]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_TOILETWATER]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_TOILETWATER]->material.kShininess = 0.78125;

    meshList[GEO_TOILETSEAT] = MeshBuilder::GenerateOBJ("ToiletSeat", "OBJ//toiletSeat.obj");
    meshList[GEO_TOILETSEAT]->textureID = LoadTGA("Image//toilet.tga");
    meshList[GEO_TOILETSEAT]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_TOILETSEAT]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_TOILETSEAT]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_TOILETSEAT]->material.kShininess = 0.78125;

    meshList[GEO_WATER] = MeshBuilder::GenerateCube("Water", Color(1.f,1.f,1.f));
    meshList[GEO_WATER]->textureID = LoadTGA("Image//water.tga");
    meshList[GEO_WATER]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_WATER]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_WATER]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_WATER]->material.kShininess = 0.78125;

    meshList[GEO_SINK] = MeshBuilder::GenerateOBJ("Sink", "OBJ//sink.obj");
    meshList[GEO_SINK]->textureID = LoadTGA("Image//sink.tga");
    meshList[GEO_SINK]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_SINK]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_SINK]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_SINK]->material.kShininess = 0.78125;

    meshList[GEO_CUP] = MeshBuilder::GenerateOBJ("Cup", "OBJ//Cup.obj");
    meshList[GEO_CUP]->textureID = LoadTGA("Image//toilet.tga");
    meshList[GEO_CUP]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_CUP]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_CUP]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_CUP]->material.kShininess = 0.78125;

    meshList[GEO_BOOK] = MeshBuilder::GenerateOBJ("Book", "OBJ//book.obj");
    meshList[GEO_BOOK]->textureID = LoadTGA("Image//book.tga");
    meshList[GEO_BOOK]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_BOOK]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_BOOK]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_BOOK]->material.kShininess = 0.78125;

    meshList[GEO_HOLDER] = MeshBuilder::GenerateOBJ("Holder", "OBJ//holder.obj");
    meshList[GEO_HOLDER]->textureID = LoadTGA("Image//doorFrame.tga");
    meshList[GEO_HOLDER]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_HOLDER]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_HOLDER]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_HOLDER]->material.kShininess = 0.78125;

    meshList[GEO_TEXT] = MeshBuilder::GenerateText("Text", 16, 16);
    meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

    Mtx44 projection;
    projection.SetToPerspective(60.f, (float)(4.f / 3.f), 0.01f, 1000.f);
    projectionStack.LoadMatrix(projection);
}



void Assignment3::Update(double dt)
{
    
    if (Application::IsKeyPressed('1')){ //enable back face culling
        glEnable(GL_CULL_FACE);
    }

    if (Application::IsKeyPressed('2')){ //disable back face culling
        glDisable(GL_CULL_FACE);
    }

    if (Application::IsKeyPressed('3')){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
    }
    if (Application::IsKeyPressed('4')){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
    }

    camera.Update(dt);

    //Light Ball
    if (Application::IsKeyPressed('I')){
        light[0].position.z += (float)(LSPEED * dt);
    }
    if (Application::IsKeyPressed('K')){
        light[0].position.z -= (float)(LSPEED * dt);
    }
    if (Application::IsKeyPressed('J')){
        light[0].position.x += (float)(LSPEED * dt);
    }
    if (Application::IsKeyPressed('L')){
        light[0].position.x -= (float)(LSPEED * dt);
    }
    if (Application::IsKeyPressed('O')){
        light[0].position.y += (float)(LSPEED * dt);
    }
    if (Application::IsKeyPressed('P')){
        light[0].position.y -= (float)(LSPEED * dt);
    }

    if (Application::IsKeyPressed('E')){
        if (((camera.position.x <= 86 && camera.position.x >= 56) && (camera.position.z <= 92 && camera.position.z >= 50)) && canCoke == false)
        {
            canCoke = true;

        }
        if ((camera.position.x >= -90 && camera.position.x <= -40) && (camera.position.z >= -87 && camera.position.z <= -50)){
            door = true;
        }
        if ((camera.position.x >= 15 && camera.position.x <= 100) && (camera.position.z >= -61 && camera.position.z <= -35)){
            camera.position.x = 70;
            camera.position.z = -82;
            camera.position.y -= 20;

            camera.target.x = camera.position.x;
            camera.target.y = 1000;
            camera.target.z = camera.position.z;

            camera.up = (5, 1, 1);

            if (light[0].power != 0.f){
                light[0].power = 0.f;
            }
            glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);

            sleepBed = true;
            camera.asleep = true;
        }
        if ((camera.position.x >= -100 && camera.position.x <= -55) && (camera.position.z >= -168 && camera.position.z <= -130)){
            water = true;
        }
    }
    if (Application::IsKeyPressed('U')){
        if (canCoke == true){
            canCoke = false;
            translateCan = 200;
        }
        if (sleepBed == true){
            camera.up = camera.defaultUp;
            camera.position = Vector3(60.f,50.f,-55.f);
            camera.target = Vector3(70, 50, -82);
            sleepBed = false;
            camera.asleep = false;
            
                light[0].power = 1.f;
            
            glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
            
        }
       
    }
    if (door == true){
        if (translateDoor < 40)
            translateDoor += (float)(20 * dt);
    }

    if (Application::IsKeyPressed('R')){
        translateCan = 0;
        translateDoor = 0;
        canCoke = false;
        door = false;
        camera.asleep = false;
        sleepBed = false;
        water = false;
    }
}



void Assignment3::Render()
{

    if (light[1].type == Light::LIGHT_DIRECTIONAL){

        Vector3 lightDir1(light[1].position.x, light[1].position.y, light[1].position.z);
        Vector3 lightDirection_cameraspace1 = viewStack.Top() * lightDir1;
        glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace1.x);

    }
    else if (light[1].type == Light::LIGHT_SPOT){

        Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
        glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);

        Vector3 spotDirection_cameraspace1 = viewStack.Top() * light[1].spotDirection;
        glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace1.x);

    }
    else{

        Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
        glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);

    }

    if (light[0].type == Light::LIGHT_DIRECTIONAL){

        Vector3 lightDir(light[0].position.x, light[0].position.y, light[0].position.z);
        Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);

    }
    else if (light[0].type == Light::LIGHT_SPOT){

        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

        Vector3 spotDirection_cameraspace = viewStack.Top() * light[0].spotDirection;
        glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);

    }
    else{

        Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
        glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

    }

    
    // Render VBO here

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewStack.LoadIdentity();

    viewStack.LookAt(
        camera.position.x, camera.position.y, camera.position.z,
        camera.target.x, camera.target.y, camera.target.z,
        camera.up.x, camera.up.y, camera.up.z
        );

    modelStack.LoadIdentity();


    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();


    Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
    glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

    Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
    glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);

    modelStack.PushMatrix();

    //Transformation stuff
    RenderSkybox();
    modelStack.PopMatrix();

    //modelStack.PushMatrix();

    ////Transformation stuff

    //modelStack.Translate(0, 1, 0);
    //RenderMesh(meshList[GEO_AXES], false);

    //modelStack.PopMatrix();


    modelStack.PushMatrix();

    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Scale(0.5, 0.5, 0.5);
    modelStack.Translate(light[1].position.x, light[1].position.y, light[1].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 88, 0);
    modelStack.Scale(1.5f, 1.5f, 1.5f);
    RenderMesh(meshList[GEO_LAMP], true);

    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(60, 0.1, -80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(3.f, 3.f, 3.f);
    RenderMesh(meshList[GEO_BED], true);

    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(60, 0, -80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(3.f, 3.f, 3.f);
    RenderMesh(meshList[GEO_MATTRESS], true);

    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(60, 0, 80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(3.f, 3.f, 3.f);
    RenderMesh(meshList[GEO_DESK], true);

    modelStack.PopMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(80, 30, 80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_DESKLAMP], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-75, 0, -100);
    modelStack.Scale(1, 1.1f, 1);
    RenderMesh(meshList[GEO_DOORFRAME], true);
    modelStack.PopMatrix();


    modelStack.PushMatrix();
    modelStack.Translate(-75, 0, -102);
    modelStack.Translate(translateDoor, 0, 0);
    modelStack.Scale(1.1f, 1.1f, 1);
    RenderMesh(meshList[GEO_DOOR], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(25, 0, -150);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(15.f, 15.f, 15.f);
    RenderMesh(meshList[GEO_TOILET], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(25, 0, -150);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(15.f, 15.f, 14.8f);
    RenderMesh(meshList[GEO_TOILETWATER], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(25, 0, -150);
    RenderMesh(meshList[GEO_WATER], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(25, 0, -150);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Translate(10, 50, 0);
    modelStack.Rotate(90, 0, 0, 1);
    modelStack.Scale(15.f, 15.f, 15.f);
    RenderMesh(meshList[GEO_TOILETSEAT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-85, 0, -150);
    modelStack.Rotate(90, 0, 1, 0);
    modelStack.Scale(4.f, 4.f, 4.f);
    RenderMesh(meshList[GEO_SINK], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(80, 30, 70);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_CUP], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(70, 30, 80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(3, 3, 3);
    RenderMesh(meshList[GEO_BOOK], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(40, 30, 80);
    modelStack.Rotate(180, 0, 1, 0);
    modelStack.Scale(1.5, 1.5, 1.5);
    RenderMesh(meshList[GEO_HOLDER], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-88, 36, -150);
    if (water == true)
        modelStack.Scale(0.6f, 12.f, 0.6f);
    if (water == false)
        modelStack.Scale(0.1f, 0.1f, 0.1f);

    RenderMesh(meshList[GEO_WATER], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-80, 15, -150);
    if (water == true)
        modelStack.Scale(10.f, 15.f, 10.f);

    if (water == false)
        modelStack.Scale(0.1f, 0.1f, 0.1f);
    RenderMesh(meshList[GEO_TOILETWATER], true);
    modelStack.PopMatrix();

    RenderTextOnScreen(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0), 100, 20, 20);

    if (canCoke == false){
        modelStack.PushMatrix();
        modelStack.Translate(60, 30, 65);
        modelStack.Rotate(180, 0, 1, 0);
        modelStack.Translate(translateCan, translateCan, translateCan);
        RenderMesh(meshList[GEO_CAN], true);
        modelStack.PopMatrix();
    }
    if (canCoke == true){
  
        glDisable(GL_DEPTH_TEST);
        //Add these code just after glDisable(GL_DEPTH_TEST);
        Mtx44 ortho;
        ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
        projectionStack.PushMatrix();
        projectionStack.LoadMatrix(ortho);
        viewStack.PushMatrix();
        viewStack.LoadIdentity(); //No need camera for ortho mode
        modelStack.PushMatrix();
        modelStack.LoadIdentity(); //Reset modelStack
        modelStack.Translate(2, -4, 0);
        modelStack.Rotate(180, 0, 1, 0);
        modelStack.Scale(5, 5, 5);
        RenderMesh(meshList[GEO_CAN], true);
        projectionStack.PopMatrix();
        viewStack.PopMatrix();
        modelStack.PopMatrix();
        glEnable(GL_DEPTH_TEST);
    }

}

void Assignment3::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}

void Assignment3::RenderText(Mesh* mesh, std::string text, Color color)
{
        if (!mesh || mesh->textureID <= 0) //Proper error check
            return;

        glDisable(GL_DEPTH_TEST);


        glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
        glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
        for (unsigned i = 0; i < text.length(); ++i)
        {
            Mtx44 characterSpacing;
            characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
            Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
            glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
            
            mesh->Render((unsigned)text[i] * 6, 6);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        glUniform1i(m_parameters[U_TEXT_ENABLED], 0);


        glEnable(GL_DEPTH_TEST);

    
}


void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
    glDisable(GL_DEPTH_TEST);
    //Add these code just after glDisable(GL_DEPTH_TEST);
    Mtx44 ortho;
    ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
    projectionStack.PushMatrix();
    projectionStack.LoadMatrix(ortho);
    viewStack.PushMatrix();
    viewStack.LoadIdentity(); //No need camera for ortho mode
    modelStack.PushMatrix();
    modelStack.LoadIdentity(); //Reset modelStack
    modelStack.Translate(24, 15, 0);
    modelStack.Scale(3, 3, 3);
    RenderText(mesh, text, Color(0, 1, 0));
    projectionStack.PopMatrix();
    viewStack.PopMatrix();
    modelStack.PopMatrix();
}



void Assignment3::RenderMesh(Mesh *mesh, bool enableLight){

    Mtx44 MVP, modelView, modelView_inverse_transpose;

    MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();

    glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
    modelView = viewStack.Top() * modelStack.Top();
    glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

    if (enableLight)
    {
        glUniform1i(m_parameters[U_LIGHTENABLED], 1);
        modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
        glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);


        //load material
        glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
        glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
        glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
        glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);

    }
    else{

        glUniform1i(m_parameters[U_LIGHTENABLED], 0);
    }

    if (mesh->textureID > 0)
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, mesh->textureID);
        glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
    }

    else
    {
        glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
    }

    mesh->Render();//Called Once

    if (mesh->textureID > 0)
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }


}


void Assignment3::RenderSkybox()
{
    //******************************************FRONT WALL
    modelStack.PushMatrix();

    modelStack.Translate(-100, 50, 60);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 80);

    //scale, translate, rotate
    RenderMesh(meshList[GEO_LEFT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(-100, 50, -40);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 120);

    //scale, translate, rotate
    RenderMesh(meshList[GEO_FRONT], true);
    modelStack.PopMatrix();
    //******************************************TOP
    modelStack.PushMatrix();
    modelStack.Translate(0, 100, 0);
    modelStack.Rotate(180.f, 0, 0, 1);
    modelStack.Scale(200, 1, 200);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_TOP], true);
    modelStack.PopMatrix();
    //******************************************BACK WALL
    modelStack.PushMatrix();

    modelStack.Translate(100, 50, 50);
    modelStack.Rotate(180.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 100);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BACK], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(100, 50, -50);
    modelStack.Rotate(180.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 100);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_LEFT], true);
    modelStack.PopMatrix();
    //******************************************LEFT WALL
    modelStack.PushMatrix();
    modelStack.Translate(0, 50, 100);
    modelStack.Rotate(90.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 200);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_LEFT], true);
    modelStack.PopMatrix();
    //******************************************RIGHT WALL
    modelStack.PushMatrix();
    modelStack.Translate(25, 50, -100);
    modelStack.Rotate(-90.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_RIGHT], true);
    modelStack.PopMatrix();
    //******************************************BOTTOM
    modelStack.PushMatrix();
    modelStack.Scale(200, 1, 200);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BOTTOM], true);
    modelStack.PopMatrix();

    //******************************************************************BATHROOM
    //***************************************************BATHBOTTOM
    modelStack.PushMatrix();
    modelStack.Translate(-25, 0, -175);
    modelStack.Scale(150, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHBOTTOM], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(-100, 50, -175);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 150);

    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHFRONT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-25, 50, -250);
    modelStack.Rotate(-90.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHRIGHT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    modelStack.Translate(50, 50, -175);
    modelStack.Rotate(180.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHBACK], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(25, 50, -100.1);
    modelStack.Rotate(90.f, 0, 1, 0);
    modelStack.Rotate(-90.f, 0, 0, 1);
    modelStack.Scale(100, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHLEFT], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-25, 100, -175);
    modelStack.Rotate(180.f, 0, 0, 1);
    modelStack.Scale(150, 1, 150);
    //scale, translate, rotate
    RenderMesh(meshList[GEO_BATHTOP], true);
    modelStack.PopMatrix();
}

