#include "Camera.h"
#include "Application.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
Camera::Camera():
distance(50),
theta(10),
phi(10)
{
    
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
Camera::~Camera()
{

}

/******************************************************************************/
/*!
\brief
Initialize camera

\param pos - position of camera
\param target - where the camera is looking at
\param up - up vector of camera
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this -> position = pos;
    this -> target = target;
    this -> up = up;

}

/******************************************************************************/
/*!
\brief
Reset the camera settings
*/
/******************************************************************************/
void Camera::Reset()
{

}

/******************************************************************************/
/*!
\brief
To be called every frame. Camera will get user inputs and update its position and orientation

\param dt - frame time
*/
/******************************************************************************/
void Camera::Update(double dt)
{

    //ZOOM IN double speed
    if (Application::IsKeyPressed('O')){

        distance -= 2 * (float)(50 * dt);
    }

    // //ZOOM OUT double speed
    if (Application::IsKeyPressed('P')){

        distance += 2 * (float)(50 * dt);

    }


    //LEFT
    if (Application::IsKeyPressed('A')){

            phi += (float)(100 * dt);

    }

    //RIGHT
    if (Application::IsKeyPressed('D')){

        float strafeYROT;
            phi -= (float)(100 * dt);


    }

    //UP
    if (Application::IsKeyPressed('W')){

        if (theta <= 60.0f){
            theta += (float)(100 * dt);
        }

    }

    //DOWN
    if (Application::IsKeyPressed('S')){

        if (theta >= -60.0f){
            theta -= (float)(100 * dt);
        }
        
    }


    position.Set(camX(theta, phi), camY(theta, phi), camZ(theta, phi));
}

float Camera::camX(float x, float y){

    return cos(Math::DegreeToRadian(x))*cos(Math::DegreeToRadian(y)) * distance;

}

float Camera::camY(float x, float y){

    return sin(Math::DegreeToRadian(x)) * distance;

}

float Camera::camZ(float x, float y){

    return cos(Math::DegreeToRadian(x))*sin(Math::DegreeToRadian(y))*distance;

}
