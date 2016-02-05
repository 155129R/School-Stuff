#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"
#include <iostream>


bool sleep;

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
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera2::Update(double dt)
{
	static const float CAMERA_SPEED = 80.f;
	static float WALK_SPEED = 30.f;
    std::cout << "CAMERA Pos: " << position << std::endl;

        if (Application::IsKeyPressed(VK_UP))
        {
            float pitch = (float)(-CAMERA_SPEED * dt);
            Vector3 view = (target - position).Normalized();
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
            Vector3 view = (target - position).Normalized();
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
            Vector3 view = (target - position).Normalized();
            Mtx44 rotation;
            rotation.SetToRotation(-yaw, 0, 1, 0);
            up = rotation * up;
            view = rotation * view;
            target = position + view;
        }
        if (Application::IsKeyPressed(VK_RIGHT))
        {
            float yaw = (float)(-CAMERA_SPEED * dt);
            Vector3 view = (target - position).Normalized();
            Mtx44 rotation;
            rotation.SetToRotation(yaw, 0, 1, 0);
            up = rotation * up;
            view = rotation * view;
            target = position + view;
        }

        if (Application::IsKeyPressed('W'))
        {
            Vector3 view = (target - position).Normalized();

            position.x += view.x * (float)(WALK_SPEED * dt);
            position.z += view.z * (float)(WALK_SPEED * dt);
            target.x += view.x * (float)(WALK_SPEED * dt);
            target.z += view.z * (float)(WALK_SPEED * dt);

        }
        if (Application::IsKeyPressed('S'))
        {
            Vector3 view = (target - position).Normalized();

            position.x -= view.x * (float)(WALK_SPEED * dt);
            position.z -= view.z * (float)(WALK_SPEED * dt);
            target.x -= view.x * (float)(WALK_SPEED * dt);
            target.z -= view.z * (float)(WALK_SPEED * dt);
        }
        if (Application::IsKeyPressed('A'))
        {
            Vector3 view = (target - position).Normalized();
            Vector3 right = view.Cross(up);
            position -= right * (float)(WALK_SPEED * dt);
            target -= right * (float)(WALK_SPEED * dt);
        }
        if (Application::IsKeyPressed('D'))
        {
            Vector3 view = (target - position).Normalized();
            Vector3 right = view.Cross(up);
            position += right * (float)(WALK_SPEED * dt);
            target += right * (float)(WALK_SPEED * dt);
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
        if (Application::IsKeyPressed(VK_SPACE))
        {
            if (flyMode == true){
                Vector3 view = (target - position).Normalized();
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
}