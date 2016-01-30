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
        GEO_SPHERE,
        GEO_PLANETS,
        GEO_MOONIA,
        GEO_PLANET1,
        GEO_MOON1A,
        GEO_RING1,
        GEO_LIGHTBALL,
        GEO_MERCURY,
        GEO_URANUS,
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
        GEO_MODEL1,
        GEO_MODEL2,
        GEO_MODEL3,
        GEO_MODEL4,
        GEO_MODEL5,
        GEO_MODEL6,
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

    unsigned m_vertexArrayID;
    Mesh *meshList[NUM_GEOMETRY];

    unsigned m_programID;
    unsigned m_parameters[U_TOTAL];

    float LSPEED;

    Camera2 camera;

    MS modelStack, viewStack, projectionStack;

    Light light[1];

    void RenderSkybox();
};

#endif
