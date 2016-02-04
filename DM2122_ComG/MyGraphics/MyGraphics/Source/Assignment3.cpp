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
    m_programID = LoadShaders("Shader//Shading.vertexshader", "Shader//LightSource.fragmentshader");
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Texture.fragmentshader");
    m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Blending.fragmentshader");


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
    m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

    //Texture
    m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
    m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");


    glUseProgram(m_programID);



    //Light Object
    light[0].type = Light::LIGHT_SPOT;
    light[0].position.Set(0, 95, 0);
    light[0].color.Set(1, 1, 1);
    light[0].power = 1;
    light[0].kC = 1.f;
    light[0].kL = 0.01f;
    light[0].kQ = 0.001f;
    light[0].cosCutOff = cos(Math::DegreeToRadian(45));
    light[0].cosInner = cos(Math::DegreeToRadian(30));
    light[0].exponent = 3.f;
    light[0].spotDirection.Set(0.f, 1.f, 0.f);


    // Make sure you pass uniform parameters after glUseProgram

    glUniform1i(m_parameters[U_NUMLIGHTS], 1);
    glUniform1i(m_parameters[U_LIGHT0_TYPE], light[0].type);
    glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
    glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
    glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
    glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
    glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);
    glUniform1f(m_parameters[U_LIGHT0_cosCutOff], light[0].cosCutOff);
    glUniform1f(m_parameters[U_LIGHT0_COSINNER], light[0].cosInner);
    glUniform1f(m_parameters[U_LIGHT0_EXPONENT], light[0].exponent);

    // Get a handle for our "MVP" uniform
    m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");

    //variable to rotate geometry


    //Initialize camera settings
    camera.Init(Vector3(0, 40, 1), Vector3(0, 40, 0), Vector3(0, 1, 0));


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

    //meshList[GEO_CHAR] = MeshBuilder::GenerateOBJ("Char", "OBJ//mattress.obj");
    //meshList[GEO_CHAR]->textureID = LoadTGA("Image//mattress.tga");
    //meshList[GEO_CHAR]->material.kAmbient.Set(0.6, 0.6, 0.6);
    //meshList[GEO_CHAR]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    //meshList[GEO_CHAR]->material.kSpecular.Set(0.45, 0.55, 0.45);
    //meshList[GEO_CHAR]->material.kShininess = 0.78125;

    meshList[GEO_DESKLAMP] = MeshBuilder::GenerateOBJ("Char", "OBJ//desklamp.obj");
    meshList[GEO_DESKLAMP]->textureID = LoadTGA("Image//metal.tga");
    meshList[GEO_DESKLAMP]->material.kAmbient.Set(0.6, 0.6, 0.6);
    meshList[GEO_DESKLAMP]->material.kDiffuse.Set(0.1, 0.35, 0.1);
    meshList[GEO_DESKLAMP]->material.kSpecular.Set(0.45, 0.55, 0.45);
    meshList[GEO_DESKLAMP]->material.kShininess = 0.78125;

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
        if (((camera.position.x <= 70 && camera.position.x >= 50) && (camera.position.z <= 60 && camera.position.z >= 45)) && ((camera.target.x <= 63 && camera.target.x >= 55) && (camera.target.z <= 56.8 && camera.target.z >= 54) && (camera.target.y<=40 && camera.target.y >= 36) )&& canCoke == false)
        {
            canCoke = true;
            
        }

    }
    if (Application::IsKeyPressed('U')){
        if (canCoke == true){
            canCoke = false;
            translateCan = 200;
        }
    }

    if (Application::IsKeyPressed('R')){
        translateCan = 0;
        canCoke = false;
    }
}



void Assignment3::Render()
{

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

    modelStack.PushMatrix();

    //Transformation stuff
    RenderSkybox();
    modelStack.PopMatrix();

    modelStack.PushMatrix();

    //Transformation stuff
   

    RenderMesh(meshList[GEO_AXES], false);

    modelStack.PopMatrix();


    modelStack.PushMatrix();

    modelStack.Translate(light[0].position.x, light[0].position.y, light[0].position.z);
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
    if (canCoke == false){
        modelStack.Translate(60, 30, 65);
        modelStack.Rotate(180, 0, 1, 0);
        modelStack.Translate(translateCan, translateCan, translateCan);
        RenderMesh(meshList[GEO_CAN], true);
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

    }
    glEnable(GL_DEPTH_TEST);

    modelStack.PopMatrix();
    modelStack.PushMatrix();
    modelStack.Translate(80, 30, 80);
    modelStack.Rotate(180, 0, 1, 0);
    RenderMesh(meshList[GEO_DESKLAMP], true);
    modelStack.PopMatrix();

}

void Assignment3::Exit()
{
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteProgram(m_programID);
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
    modelStack.Translate(-25,0,-175);
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
    modelStack.Scale(size, size, size);
    modelStack.Translate(x, y, 0);
}