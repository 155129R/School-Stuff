#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Camera.h"
#include "TAABB.h"

class Camera2 : public Camera
{
public:
    //Vector3 position;
    //Vector3 target;
    //Vector3 up;


    Vector3 defaultPosition;
    Vector3 defaultTarget;
    Vector3 defaultUp;
    bool flyMode = false;
    bool asleep = false;
    Camera2();
    ~Camera2();
    virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
    virtual void Update(double dt);
    virtual void Reset();

private:
    TAABB frontWall;
    TAABB roomBackWall;
    TAABB roomLeftWall;
    TAABB commonWall;
    TAABB toiletBackWall;
    TAABB toiletLeftWall;
    TAABB bed;
    TAABB table;
    TAABB sink;
    TAABB toilet;

};

#endif