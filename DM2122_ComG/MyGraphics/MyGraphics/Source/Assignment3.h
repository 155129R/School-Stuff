#ifndef ASSIGNMENT3_H
#define ASSIGNMENT3_H


#include "Scene.h"
#include "Camera2.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"

class Assignment3 : public Scene
{
    enum GEOMETRY_TYPE
    {
        GEO_AXES,
        GEO_QUAD,
        GEO_CUBE,
        GEO_CIRCLE,
        GEO_RING,
        GEO_LIGHTBALL,
        GEO_HEMISHERE,
        GEO_CONE,
        GEO_LEFT,
        GEO_RIGHT,
        GEO_TOP,
        GEO_BOTTOM,
        GEO_FRONT,
        GEO_BACK,
        GEO_BATHLEFT,
        GEO_BATHRIGHT,
        GEO_BATHTOP,
        GEO_BATHBOTTOM,
        GEO_BATHFRONT,
        GEO_BATHBACK,
        GEO_LAMP,
        GEO_CAN,
        GEO_BED,
        GEO_MATTRESS,
        GEO_DESK,
        GEO_CHAR,
        GEO_DESKLAMP,
        NUM_GEOMETRY,
    };
    enum UNIFORM_TYPE
    {
        U_MVP = 0,
        U_MODELVIEW,
        U_MODELVIEW_INVERSE_TRANSPOSE,
        U_MATERIAL_AMBIENT,
        U_MATERIAL_DIFFUSE,
        U_MATERIAL_SPECULAR,
        U_MATERIAL_SHININESS,
        U_LIGHT0_POSITION,
        U_LIGHT0_COLOR,
        U_LIGHT0_POWER,
        U_LIGHT0_KC,
        U_LIGHT0_KL,
        U_LIGHT0_KQ,
        U_LIGHTENABLED,
        U_LIGHT0_TYPE,
        U_LIGHT0_SPOTDIRECTION,
        U_LIGHT0_cosCutOff,
        U_LIGHT0_COSINNER,
        U_LIGHT0_EXPONENT,
        U_NUMLIGHTS,
        U_COLOR_TEXTURE_ENABLED,
        U_COLOR_TEXTURE,
        U_TOTAL,
    };
public:
    Assignment3();
    ~Assignment3();

    Mtx44 MVP;

    virtual void Init();
    virtual void Update(double dt);
    virtual void Render();
    virtual void Exit();
private:
    void RenderMesh(Mesh *mesh, bool enablelight);
    void Assignment3::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float LSPEED;
    float translateCan;
    Camera2 camera;

    MS modelStack, viewStack, projectionStack;

    Light light[1];

    void RenderSkybox();

    float valueZ;
    bool canCoke = false;
};

#endif
