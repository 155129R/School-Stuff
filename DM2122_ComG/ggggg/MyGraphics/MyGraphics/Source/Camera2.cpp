#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"
#include <iostream>
#include "TAABB.h"

Camera2::Camera2()
{
}

Camera2::~Camera2()
{
}

void Camera2::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
    this->position = defaultPosition = pos;
    this->target = defaultTarget = target;
    this->up = defaultUp = up;
    Vector3 view = (target - position).Normalized();
    Vector3 right = view.Cross(up);
    right.y = 0;
    right.Normalize();
    this->up = defaultUp = right.Cross(view).Normalized();
    frontWall = TAABB(Vector3(-102.f, 0.f, -260.f), Vector3(-98.f, 99.f, 116.f));
    roomBackWall = TAABB(Vector3(99.f, 0.f, -99.f), Vector3(101.f, 99.f, 99.f));
    roomLeftWall = TAABB(Vector3(-99.f, 0.f, 99.f), Vector3(99.f, 99.f, 101.f));
    commonWall = TAABB(Vector3(-50.f, 0.f, -102.f), Vector3(99.f, 99.f, -98.f));
    toiletBackWall = TAABB(Vector3(50.f, 0.f, -249.f), Vector3(55.f, 99.f, -102.f));
    toiletLeftWall = TAABB(Vector3(-99.f, 0.f, -252.f), Vector3(50.f, 99.f, -248.f));
    bed = TAABB(Vector3(15.f, 0.f, -100.f), Vector3(100.f, 51.f, -62.f));
    table = TAABB(Vector3(26.f, 0.f, 60.f), Vector3(88.f, 51.f, 92.f));
    sink = TAABB(Vector3(-100.f, 0.f, -162.f), Vector3(-70.f, 51.f, -132.f));
    toilet = TAABB(Vector3(4.f, 0.f, -164.f), Vector3(51.f, 51.f, -134.f));
       
}

void Camera2::Update(double dt)
{
    static const float CAMERA_SPEED = 80.f;
    static float WALK_SPEED = 30.f;
    Vector3 view = (target - position).Normalized();

    if (asleep == false){
        if (Application::IsKeyPressed(VK_UP))
        {
            float pitch = (float)(-CAMERA_SPEED * dt);

            Vector3 right = view.Cross(up);
            right.y = 0;
            right.Normalize();
            up = right.Cross(view).Normalized();
            Mtx44 rotation;
            if (view.y < 0.93){
                rotation.SetToRotation(-pitch, right.x, right.y, right.z);
                view = rotation * view;
                target = position + view;

            }

        }
        if (Application::IsKeyPressed(VK_DOWN))
        {
            float pitch = (float)(CAMERA_SPEED * dt);
            Vector3 right = view.Cross(up);
            right.y = 0;
            right.Normalize();
            up = right.Cross(view).Normalized();
            Mtx44 rotation;
            if (view.y > -0.8){
                rotation.SetToRotation(-pitch, right.x, right.y, right.z);
                view = rotation*view;
                target = position + view;
            }


        }

        if (Application::IsKeyPressed(VK_LEFT))
        {
            float yaw = (float)(-CAMERA_SPEED * dt);

            Mtx44 rotation;
            rotation.SetToRotation(-yaw, 0, 1, 0);
            up = rotation * up;
            view = rotation * view;
            target = position + view;
        }
        if (Application::IsKeyPressed(VK_RIGHT))
        {
            float yaw = (float)(-CAMERA_SPEED * dt);

            Mtx44 rotation;
            rotation.SetToRotation(yaw, 0, 1, 0);
            up = rotation * up;
            view = rotation * view;
            target = position + view;
        }
        if (flyMode == false){
            if (PointInAABB(frontWall, position + view) == false){
                if (PointInAABB(roomBackWall, position + view) == false)
                if (PointInAABB(roomLeftWall, position + view) == false)
                if (PointInAABB(commonWall, position + view) == false)
                if (PointInAABB(toiletBackWall, position + view) == false)
                if (PointInAABB(toiletLeftWall, position + view) == false)
                if (PointInAABB(bed, position + view) == false)
                if (PointInAABB(table, position + view) == false)
                if (PointInAABB(sink, position + view) == false)
                if (PointInAABB(toilet, position + view) == false)

                if (Application::IsKeyPressed('W'))
                {


                    position.x += view.x * (float)(WALK_SPEED * dt);
                    position.z += view.z * (float)(WALK_SPEED * dt);
                    target.x += view.x * (float)(WALK_SPEED * dt);
                    target.z += view.z * (float)(WALK_SPEED * dt);

                }

            }
            if (PointInAABB(frontWall, position - view) == false){
                if (PointInAABB(roomBackWall, position - view) == false)
                if (PointInAABB(roomLeftWall, position - view) == false)
                if (PointInAABB(commonWall, position - view) == false)
                if (PointInAABB(toiletBackWall, position - view) == false)
                if (PointInAABB(toiletLeftWall, position - view) == false)
                if (PointInAABB(bed, position - view) == false)
                if (PointInAABB(table, position - view) == false)
                if (PointInAABB(sink, position - view) == false)
                if (PointInAABB(toilet, position - view) == false)

                if (Application::IsKeyPressed('S'))
                {


                    position.x -= view.x * (float)(WALK_SPEED * dt);
                    position.z -= view.z * (float)(WALK_SPEED * dt);
                    target.x -= view.x * (float)(WALK_SPEED * dt);
                    target.z -= view.z * (float)(WALK_SPEED * dt);
                }


            }
            if (PointInAABB(frontWall, position - view.Cross(up)) == false){
                if (PointInAABB(roomBackWall, position - view.Cross(up)) == false)
                if (PointInAABB(roomLeftWall, position - view.Cross(up)) == false)
                if (PointInAABB(commonWall, position - view.Cross(up)) == false)
                if (PointInAABB(toiletBackWall, position - view.Cross(up)) == false)
                if (PointInAABB(toiletLeftWall, position - view.Cross(up)) == false)
                if (PointInAABB(bed, position - view.Cross(up)) == false)
                if (PointInAABB(table, position - view.Cross(up)) == false)
                if (PointInAABB(sink, position - view.Cross(up)) == false)
                if (PointInAABB(toilet, position - view.Cross(up)) == false)

                if (Application::IsKeyPressed('A'))
                {

                    Vector3 right = view.Cross(up);
                    position -= right * (float)(WALK_SPEED * dt);
                    target -= right * (float)(WALK_SPEED * dt);
                }


            }
            if (PointInAABB(frontWall, position + view.Cross(up)) == false){
                if (PointInAABB(roomBackWall, position + view.Cross(up)) == false)
                if (PointInAABB(roomLeftWall, position + view.Cross(up)) == false)
                if (PointInAABB(commonWall, position + view.Cross(up)) == false)
                if (PointInAABB(toiletBackWall, position + view.Cross(up)) == false)
                if (PointInAABB(toiletLeftWall, position + view.Cross(up)) == false)
                if (PointInAABB(bed, position + view.Cross(up)) == false)
                if (PointInAABB(table, position + view.Cross(up)) == false)
                if (PointInAABB(sink, position + view.Cross(up)) == false)
                if (PointInAABB(toilet, position + view.Cross(up)) == false)

                if (Application::IsKeyPressed('D'))
                {

                    Vector3 right = view.Cross(up);
                    position += right * (float)(WALK_SPEED * dt);
                    target += right * (float)(WALK_SPEED * dt);
                }


            }
        }
        if (Application::IsKeyPressed(VK_LSHIFT))
        {

            std::cout << "Speed changed from " << WALK_SPEED;
            if (WALK_SPEED < 70)
                WALK_SPEED += 5;

            std::cout << " to " << WALK_SPEED << std::endl;

        }
        if (Application::IsKeyPressed(VK_LCONTROL))
        {
            std::cout << "Speed changed from " << WALK_SPEED;
            if (WALK_SPEED > 30)
                WALK_SPEED -= 5;
            std::cout << " to " << WALK_SPEED << std::endl;

        }
        if (flyMode == true){
            if (Application::IsKeyPressed('W'))
            {


                position.x += view.x * (float)(WALK_SPEED * dt);
                position.z += view.z * (float)(WALK_SPEED * dt);
                target.x += view.x * (float)(WALK_SPEED * dt);
                target.z += view.z * (float)(WALK_SPEED * dt);

            }

            if (Application::IsKeyPressed('S'))
            {


                position.x -= view.x * (float)(WALK_SPEED * dt);
                position.z -= view.z * (float)(WALK_SPEED * dt);
                target.x -= view.x * (float)(WALK_SPEED * dt);
                target.z -= view.z * (float)(WALK_SPEED * dt);
            }

            if (Application::IsKeyPressed('A'))
            {

                Vector3 right = view.Cross(up);
                position -= right * (float)(WALK_SPEED * dt);
                target -= right * (float)(WALK_SPEED * dt);
            }

            if (Application::IsKeyPressed('D'))
            {

                Vector3 right = view.Cross(up);
                position += right * (float)(WALK_SPEED * dt);
                target += right * (float)(WALK_SPEED * dt);
            }

            if (Application::IsKeyPressed(VK_SPACE))
            {


                position.y += view.y * (float)(WALK_SPEED * dt);
                target.y += view.y * (float)(WALK_SPEED * dt);

            }
        }
        if (Application::IsKeyPressed('F'))
        {

            flyMode = (flyMode == false) ? true : false;
            if (flyMode)
                std::cout << "Fly Mode enabled" << std::endl;
            else
                std::cout << "Fly Mode disabled" << std::endl;
        }

    }
    if (Application::IsKeyPressed('R'))
    {
        Reset();
    }


}

void Camera2::Reset()
{
    target = defaultTarget;
    up = defaultUp;
    position = defaultPosition;
    asleep = false;
    flyMode = false;
}

