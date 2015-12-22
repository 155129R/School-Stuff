#include "Assignment2.h"
#include "GL\glew.h"

#include "Utility.h"
#include "Material.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Assignment2::Assignment2() :
LSPEED(10)
{

}

Assignment2::~Assignment2()
{
}


void Assignment2::Init()
{
    // Init VBO here

    // Set background color to dark blue
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
    m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//Shading.fragmentshader");
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

    glUseProgram(m_programID);

    //Light Object

    light[0].position.Set(0, 20, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 1;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;

    // Make sure you pass uniform parameters after glUseProgram

    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
    gunBodyColor_B, gunBodyColor_G, gunBodyColor_R = 0;
    //variable to rotate body
    rotateBodyAngle = 0;

    //angler to rotate feet
    feetRot_Z = 0;

    //translate body
    translateBody_X, translateBody_Y, translateBody_Z = 0;
    translateBullet = 0;
    //Eart variables init
    earthRotAngle, earthRevAngle = 0;
    //Initialize camera settings
    camera.Init(Vector3(25, 55, 50), Vector3(0, 0, 3), Vector3(0, 1, 0));

    meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

    //meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", (0, 0, 0), 18, 36);
    //meshList[GEO_SPHERE]->material.kAmbient.Set(0.2, 0.2, 0.2);
    //meshList[GEO_SPHERE]->material.kDiffuse.Set(0.2, 0.2, 0.2);
    //meshList[GEO_SPHERE]->material.kSpecular.Set(1, 1, 1);
    //meshList[GEO_SPHERE]->material.kShininess = 1;

    meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("LightBall", Color(1, 1, 1), 18, 36);

    meshList[GEO_ALIENMOON] = MeshBuilder::GenerateCircle("AlienMoon", Color(0.6, 0.6, 0.60), 18);

    meshList[GEO_SUN] = MeshBuilder::GenerateSphere("SUN", Color(1, 1, 0), 36, 18);

    meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("EARTH", Color(0, 0.3, 0.7), 18, 36);

    //**************************************************************************************HEAD
    meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Head", Color(0.8, 1, 0), 18, 36);
    meshList[GEO_HEAD]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_HEAD]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_HEAD]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_HEAD]->material.kShininess = 0.78125;

    //**************************************************************************************COLLAR
    meshList[GEO_COLLAR] = MeshBuilder::GenerateTorus("Collar", 18, 36, 10, 3, Color(0.8, 0, 0.6));
    meshList[GEO_COLLAR]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_COLLAR]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_COLLAR]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_COLLAR]->material.kShininess = 0.78125;

    //**************************************************************************************MOUTH
    meshList[GEO_MOUTH] = MeshBuilder::GenerateCircle("MOUTH", Color(0.2, 0.5, 0), 18);
    //*************************************************************************************BODY

    meshList[GEO_BODY] = MeshBuilder::GenerateCylinder("Body", Color(0, 0.1, 0.6), 36, false);
    meshList[GEO_BODY]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_BODY]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_BODY]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_BODY]->material.kShininess = 0.9;

    //*************************************************************************************BODY

    meshList[GEO_BODY_SIDE] = MeshBuilder::GenerateHemisphere("Body_Side", Color(0, 0.1, 0.6), 18, 36);
    meshList[GEO_BODY_SIDE]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_BODY_SIDE]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_BODY_SIDE]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_BODY_SIDE]->material.kShininess = 0.9;

    //**************************************************************************************ELBOW
    meshList[GEO_ELBOW] = MeshBuilder::GenerateSphere("Elbow", Color(0, 0.1, 0.6), 18, 36);
    meshList[GEO_ELBOW]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_ELBOW]->material.kDiffuse.Set(0.6, 0.6, 0.6);
    meshList[GEO_ELBOW]->material.kSpecular.Set(0.4, 0.4, 0.4);
    meshList[GEO_ELBOW]->material.kShininess = 0.9;

    //*************************************************************************************FINGER

    meshList[GEO_FINGER] = MeshBuilder::GenerateHemisphere("Finger", Color(0.8, 1, 0), 18, 36);
    meshList[GEO_FINGER]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_FINGER]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_FINGER]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_FINGER]->material.kShininess = 0.78125;

    //**************************************************************************************Eyeball
    meshList[GEO_EYEBALL] = MeshBuilder::GenerateSphere("Eyeball", Color(1, 1, 1), 18, 36);

    //**************************************************************************************PUPILS
    meshList[GEO_PUPILS] = MeshBuilder::GenerateCircle("Circle", Color(0, 0, 0), 8);

    //*************************************************************************************Antenna Body

    meshList[GEO_ANTENNA_BODY] = MeshBuilder::GenerateHemisphere("Finger", Color(0.8, 1, 0), 18, 36);
    meshList[GEO_ANTENNA_BODY]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_ANTENNA_BODY]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_ANTENNA_BODY]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_ANTENNA_BODY]->material.kShininess = 0.78125;

    //*************************************************************************************GUN_HANDLE

    meshList[GEO_GUN_HANDLE] = MeshBuilder::GenerateCylinder("GUN_HANDLE", Color(0.4, 0.4, 0.4), 36, false);
    meshList[GEO_GUN_HANDLE]->material.kAmbient.Set(0.19225, 0.19225, 0.19225);
    meshList[GEO_GUN_HANDLE]->material.kDiffuse.Set(0.50754, 0.50754, 0.50754);
    meshList[GEO_GUN_HANDLE]->material.kSpecular.Set(0.508273, 0.508273, 0.508273);
    meshList[GEO_GUN_HANDLE]->material.kShininess = 0.4;

    //*************************************************************************************GUN_BODY
    meshList[GEO_GUN_BODY] = MeshBuilder::GenerateSphere("GUN_BODY", Color(gunBodyColor_B, gunBodyColor_G, gunBodyColor_R), 18, 36);
    meshList[GEO_GUN_BODY]->material.kAmbient.Set(0.19225, 0.19225, 0.19225);
    meshList[GEO_GUN_BODY]->material.kDiffuse.Set(0.50754, 0.50754, 0.50754);
    meshList[GEO_GUN_BODY]->material.kSpecular.Set(0.508273, 0.508273, 0.508273);
    meshList[GEO_GUN_BODY]->material.kShininess = 0.4;

    //*************************************************************************************BULLET

    meshList[GEO_BULLET] = MeshBuilder::GenerateCylinder("Bullet", Color(1, 0, 0), 36, false);

    //*************************************************************************************CRATER

    meshList[GEO_CRATER] = MeshBuilder::GenerateCylinder("CRATER", Color(0.4, 0.4, 0.4), 36, true);


    //*************************************************************************************MTX44 applied here
    Mtx44 projection;
    projection.SetToPerspective(450.f, 40.f / 30.f, 1.0f, 10000.f);
    projectionStack.LoadMatrix(projection);


}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Assignment2::Update(double dt)
{

    gunBodyColor_B = (rand() % 255 - 1) / 255.0;
    gunBodyColor_G = (rand() % 255 - 1) / 255.0;
    gunBodyColor_R = (rand() % 255 - 1) / 255.0;
    meshList[GEO_GUN_BODY] = MeshBuilder::GenerateSphere("GUN_BODY", Color(gunBodyColor_B, gunBodyColor_G, gunBodyColor_R), 18, 36);

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
    if (Application::IsKeyPressed('4')){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
    }

    camera.Update(dt);
    if (Application::IsKeyPressed('5')){

        camera.up = Vector3(0, translateBody_Y + 2, 0);
        camera.target = Vector3(translateBody_X, translateBody_Y, translateBody_Z);

    }
    earthRotAngle += (float)(0.8 * dt);
    earthRevAngle += (float)(2 * dt);
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

    if (Application::IsKeyPressed('G')){
        aimGunAngle -= (float)(2 * dt);
    }
    if (Application::IsKeyPressed('R')){
        translateBody_X = 0;
        translateBody_Y = 0;
        translateBody_Z = 0;
        rotateBodyAngle = 0;
        feetRot_Z = 0;
        translateBullet = 0;
    }
    if (Application::IsKeyPressed('F'))
    {

        translateBullet += float(30 * dt);
    }
    if (Application::IsKeyPressed('E'))
    {
        translateBullet = 0;
    }
    if (Application::IsKeyPressed('W')){
        translateBody_Z += (float)(10 * dt);

        camera.position.z += (float)(1 * dt);

        //  std::cout << "translateBody_Y = " << translateBody_Z << std::endl;


        if (translateBody_Y < 5)
        {
            translateBody_Y += (float)(10 * dt);
        }
        if (feetRot_Z < 15)
        {
            feetRot_Z += (float)(10 * dt);
        }
    }

    else if (Application::IsKeyPressed('A')){
        translateBody_X += (float)(10 * dt);
        rotateBodyAngle += (float)(10 * dt);
        camera.position.x += (float)(5 * dt);

        // std::cout << "translateBody_X =" << translateBody_X << std::endl;
        // std::cout << "rotateBodyAngle = " << rotateBodyAngle << std::endl;
        if (translateBody_Y < 5)
        {
            translateBody_Y += (float)(10 * dt);
        }
        if (feetRot_Z < 15)
        {
            feetRot_Z += (float)(10 * dt);
        }
    }

    else if (Application::IsKeyPressed('S')){
        translateBody_Z -= (float)(10 * dt);
        camera.position.z -= (float)(1 * dt);
        // std::cout << "translateBody_Z = " << translateBody_Z << std::endl;
        if (translateBody_Y < 5)
        {
            translateBody_Y += (float)(10 * dt);
        }
        if (feetRot_Z < 15)
        {
            feetRot_Z += (float)(10 * dt);
        }
    }

    else if (Application::IsKeyPressed('D')){
        translateBody_X -= (float)(10 * dt);
        rotateBodyAngle -= (float)(10 * dt);
        camera.position.x -= (float)(5 * dt);
        // std::cout <<"translateBody_X =" <<translateBody_X << std::endl;
        // std::cout << "rotateBodyAngle = " << rotateBodyAngle << std::endl;
        if (translateBody_Y < 5)
        {
            translateBody_Y += (float)(10 * dt);
        }
        if (feetRot_Z < 15)
        {
            feetRot_Z += (float)(10 * dt);
        }
    }

    else{
        if (translateBody_Y >= 0){
            translateBody_Y -= (float)(10 * dt);
        }
        if (feetRot_Z >= 0)
        {
            feetRot_Z -= (float)(10 * dt);
        }
    }



}

void Assignment2::Render()
{

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

    modelStack.PushMatrix();

    modelStack.Rotate(rotateBodyAngle, 0, 1, 0);

    modelStack.PushMatrix();
    modelStack.Translate(translateBody_X, translateBody_Y, translateBody_Z);

    //**********************************************************************************************Render Head
    modelStack.PushMatrix();

    modelStack.Translate(0, 27, 0);
    modelStack.Scale(7, 4, 5);

    RenderMesh(meshList[GEO_HEAD], true);

    modelStack.PopMatrix();

    //*******************************************************RENDER EYES

    //MIDDLE EYE
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0.f, 29, 3.7);
    modelStack.Scale(1.5, 1.2, 1.2);
    RenderMesh(meshList[GEO_EYEBALL], false);

    modelStack.PopMatrix();
    //MIDDLE EYE PUPIL
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0.f, 29, 4.9);
    modelStack.Rotate(90.f, 90, 1, 0);
    modelStack.Scale(0.6, 0.6, 0.6);
    RenderMesh(meshList[GEO_PUPILS], false);
    modelStack.PopMatrix();
    //RIGHT EYE
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-3.f, 28.5, 3.7);

    modelStack.Scale(1.5, 1.2, 1.2);
    RenderMesh(meshList[GEO_EYEBALL], false);


    modelStack.PopMatrix();
    //RIGHT EYE PUPIL
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-3.f, 28.5, 4.9);
    modelStack.Rotate(90.f, 90, 1, 0);
    modelStack.Scale(0.6, 0.6, 0.6);
    RenderMesh(meshList[GEO_PUPILS], false);
    modelStack.PopMatrix();

    //LEFT EYE
    modelStack.PushMatrix();

    modelStack.Translate(3.f, 28.5, 3.7);

    modelStack.Scale(1.5, 1.2, 1.2);
    RenderMesh(meshList[GEO_EYEBALL], false);


    modelStack.PopMatrix();
    //LEFT EYE PUPIL
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(3.f, 28.5, 4.9);
    modelStack.Rotate(90.f, 90, 1, 0);
    modelStack.Scale(0.6, 0.6, 0.6);
    RenderMesh(meshList[GEO_PUPILS], false);
    modelStack.PopMatrix();
    //*******************************************************CLOSE EYES
    //*******************************************************RENDER ANTENNA
    modelStack.PushMatrix();

    //******************************BASE
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0.f, 30.5, 0);
    modelStack.Rotate(180.f, 0, 0, 1);
    modelStack.Scale(0.8, 0.8, 0.8);
    RenderMesh(meshList[GEO_FINGER], true);
    modelStack.PopMatrix();

    //Antenna body
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0.f, 34, 0);

    modelStack.Scale(0.3, 5, 0.3);
    RenderMesh(meshList[GEO_ANTENNA_BODY], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0.f, 34, 0);

    modelStack.Scale(0.6, 0.6, 0.6);
    RenderMesh(meshList[GEO_HEAD], true);
    modelStack.PopMatrix();

    //*******************************************************CLOSE ANTENNA
    //EAR 1
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(6.f, 28, 0);
    modelStack.Rotate(180.f, 0, 0, 1);
    modelStack.Scale(0.6, 3, 2);
    RenderMesh(meshList[GEO_FINGER], true);
    modelStack.PopMatrix();

    //EAR 2
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-6.f, 28, 0);
    modelStack.Rotate(180.f, 0, 0, 1);
    modelStack.Scale(0.6, 3, 2);
    RenderMesh(meshList[GEO_FINGER], true);
    modelStack.PopMatrix();
    //*******************************************************RENDER MOUTH

    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(0, 26, 5);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(1.5, 1, 1);
    RenderMesh(meshList[GEO_MOUTH], false);
    modelStack.PopMatrix();

    //*******************************************************CLOSE MOUTH

    //**********************************************************************************************Pop Head

    //**********************************************************************************************Render Collar
    modelStack.PushMatrix();

    modelStack.Translate(0, 24, 0);
    modelStack.Scale(0.5, 0.4, 0.3);

    RenderMesh(meshList[GEO_COLLAR], true);


    modelStack.PopMatrix();
    //**********************************************************************************************Pop Collar

    //**********************************************************************************************Render body
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(5.f, 19, 0);
    modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
    modelStack.Scale(5, 10, 4);
    RenderMesh(meshList[GEO_BODY], true);


    modelStack.PopMatrix();
    //Body side
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(4.8f, 19, 0);
    modelStack.Rotate(90.f, 0.f, 0.f, 1.f);
    modelStack.Scale(5, 2, 4);
    RenderMesh(meshList[GEO_BODY_SIDE], true);


    modelStack.PopMatrix();

    //Body side 2
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-4.8f, 19, 0);
    modelStack.Rotate(270.f, 0.f, 0.f, 1.f);
    modelStack.Scale(5, 2, 4);
    RenderMesh(meshList[GEO_BODY_SIDE], true);


    modelStack.PopMatrix();
    //**********************************************************************************************Pop body render

    //**********************************************************************************************Render ARMS

    //****************************************************ARM 1
    modelStack.PushMatrix();

    modelStack.Rotate(aimGunAngle, 1.f, 0, 0);

    //ARM 1 UPPER
    modelStack.PushMatrix();
    //Transformation applied here

    modelStack.Translate(6.5f, 20, 0);
    modelStack.Rotate(60.f, 40.f, 0.f, 0.f);
    modelStack.Scale(1.5, 3, 1.5);
    RenderMesh(meshList[GEO_BODY], true);
    modelStack.PopMatrix();



    //RIGHT HAND DE ELBOW
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(6.5f, 21.7f, 3);
    modelStack.Scale(1.5f, 1.5f, 1.5f);

    RenderMesh(meshList[GEO_ELBOW], true);


    modelStack.PopMatrix();

    //ARM 1 LOWER
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(6.5f, 22., 3.3);
    modelStack.Rotate(60.f, 40.f, 0.f, 0.f);
    modelStack.Scale(1.5, 3, 1.5);
    RenderMesh(meshList[GEO_BODY], true);
    modelStack.PopMatrix();
    //Palm 1
    modelStack.PushMatrix();

    modelStack.Translate(6.5, 23.3, 5.6);
    modelStack.Scale(1.6f, 1.6f, 1.6f);

    RenderMesh(meshList[GEO_HEAD], true);

    modelStack.PopMatrix();
    //*********************************************************************************************************************GUN
    //*********************************************************************GUN_HANDLE
    modelStack.PushMatrix();
    modelStack.Translate(6.5, 24, 6);
    modelStack.Scale(0.8, 3, 0.8);
    RenderMesh(meshList[GEO_GUN_HANDLE], true);
    modelStack.PopMatrix();
    //*********************************************************************CLOSE GUN_HANDLE
    //*********************************************************************GUN_BODY
    modelStack.PushMatrix();
    modelStack.Translate(6.5, 27, 6);
    modelStack.Scale(1.3, 1.3, 1.3);
    RenderMesh(meshList[GEO_GUN_BODY], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(6.5, 27, 7.5);

    RenderMesh(meshList[GEO_GUN_BODY], true);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(6.5, 27, 8.5);
    modelStack.Scale(0.7, 0.7, 0.7);
    RenderMesh(meshList[GEO_GUN_BODY], true);
    modelStack.PopMatrix();

    //*********************************************************************CLOSE GUN_BODY
    //Bullet
    modelStack.PushMatrix();
    modelStack.Translate(6.5, 27, 6.5 + translateBullet);
    modelStack.Rotate(90, 1, 0, 0);
    modelStack.Scale(0.3, 3, 0.3);
    RenderMesh(meshList[GEO_BULLET], false);
    modelStack.PopMatrix();
    //*********************************************************************************************************************CLOSE GUN
    modelStack.PopMatrix();
    //**************************************************** close ARM 1
    //**************************************************** render ARM 2
    //ARM 2 UPPER
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-6.f, 20, 0);
    modelStack.Rotate(50.f, 0.f, 0.f, 1.f);
    modelStack.Scale(1.5, 3, 1.5);
    RenderMesh(meshList[GEO_BODY], true);


    modelStack.PopMatrix();

    //LEFT HAND DE ELBOW
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-8.f, 21.7f, 0);
    modelStack.Scale(1.4f, 1.4f, 1.4f);

    RenderMesh(meshList[GEO_ELBOW], true);


    modelStack.PopMatrix();

    //ARM 2 LOWER
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-8.4f, 22., 0);
    modelStack.Rotate(50.f, 0.f, 0.f, 1.f);
    modelStack.Scale(1.5, 3, 1.5);
    RenderMesh(meshList[GEO_BODY], true);


    modelStack.PopMatrix();

    //PALM 2

    modelStack.PushMatrix();

    modelStack.Translate(-10.8f, 24.2, 0);
    modelStack.Scale(1.6f, 1.6f, 1.6f);

    RenderMesh(meshList[GEO_HEAD], true);

    modelStack.PopMatrix();
    //*****SET 1
    //FINGER 1
    modelStack.PushMatrix();

    modelStack.Translate(-10.f, 25.f, 0);
    modelStack.Rotate(180.f, 1.f, 0.f, 0.f);
    modelStack.Scale(0.6f, 1.7f, 0.6f);
    RenderMesh(meshList[GEO_FINGER], true);

    modelStack.PopMatrix();
    //Finger 2
    modelStack.PushMatrix();

    modelStack.Translate(-10.f, 25.f, 0);
    modelStack.Rotate(180.f, 1.f, 0.f, 0.f);
    modelStack.Scale(0.6f, 1.7f, 0.6f);
    RenderMesh(meshList[GEO_FINGER], true);

    modelStack.PopMatrix();
    //*****End of SET 1

    //*****SET 2

    //*****End of SET 2
    //**************************************************** close ARM 2

    //**********************************************************************************************Render Legs

    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(2.5f, 9.5, 0);
    modelStack.Scale(3, 6, 3);
    RenderMesh(meshList[GEO_BODY], true);


    modelStack.PopMatrix();

    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-2.5f, 9.5, 0);
    modelStack.Scale(3, 6, 3);
    RenderMesh(meshList[GEO_BODY], true);


    modelStack.PopMatrix();

    //**********************************************************************************************Pop Legs
    //****************************************************RENDER FEET

    //RIGHT HAND DE ELBOW
    modelStack.PushMatrix();
    modelStack.Rotate(feetRot_Z, 1, 0, 0);
    modelStack.PushMatrix();
    //Transformation applied here

    modelStack.Translate(3.f, 8.7f, 0.8);
    modelStack.Scale(3.f, 2.5f, 4.0f);
    RenderMesh(meshList[GEO_ELBOW], true);


    modelStack.PopMatrix();

    //LEFT HAND DE ELBOW
    modelStack.PushMatrix();

    //Transformation applied here

    modelStack.Translate(-3.f, 8.7f, 0.8);
    modelStack.Scale(3.f, 2.5f, 4.0f);

    RenderMesh(meshList[GEO_ELBOW], true);


    modelStack.PopMatrix();
    modelStack.PopMatrix();
    //**************************************************** close FEET
    modelStack.PopMatrix();

    modelStack.PopMatrix();

    //modelStack.PushMatrix();

    //Transformation applied here
    //RenderMesh(meshList[GEO_AXES], false);

    //modelStack.PopMatrix();


    modelStack.PushMatrix();

    modelStack.Translate(light[0].position.x + 20, light[0].position.y + 20, light[0].position.z);
    RenderMesh(meshList[GEO_LIGHTBALL], false);
    modelStack.PopMatrix();




    //********************************************************************************************CRATER

    modelStack.PushMatrix();
    modelStack.Translate(-40, 7, 0);
    modelStack.Scale(20, 4, 20);
    RenderMesh(meshList[GEO_CRATER], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(40, 7, 80);
    modelStack.Scale(20, 4, 20);
    RenderMesh(meshList[GEO_CRATER], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(70, 7, -80);
    modelStack.Scale(20, 4, 20);
    RenderMesh(meshList[GEO_CRATER], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(-35, 7, 120);
    modelStack.Scale(20, 4, 20);
    RenderMesh(meshList[GEO_CRATER], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(60, 7, 160);
    modelStack.Scale(20, 4, 20);
    RenderMesh(meshList[GEO_CRATER], false);
    modelStack.PopMatrix();

    //********************************************************************************************CLOSE CRATER
    modelStack.PushMatrix();
    modelStack.Translate(1000, 7, 0);
    modelStack.Scale(200, 200, 200);
    RenderMesh(meshList[GEO_SUN], false);

    modelStack.PopMatrix();

    modelStack.PushMatrix();//earth
    modelStack.Rotate(-earthRevAngle, earthRevAngle, 0, 1);
    modelStack.Translate(-800, 7, -600);
    modelStack.Rotate(-earthRevAngle, earthRevAngle, 0, 1);
    modelStack.Scale(120, 120, 120);
    RenderMesh(meshList[GEO_EARTH], false);
    modelStack.PopMatrix();

    modelStack.PushMatrix();
    modelStack.Translate(0, 7, 0);
    modelStack.Scale(200, 0, 200);
    RenderMesh(meshList[GEO_ALIENMOON], false);

    modelStack.PopMatrix();

}

void Assignment2::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
}



void Assignment2::RenderMesh(Mesh *mesh, bool enableLight){

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

    mesh->Render();



}