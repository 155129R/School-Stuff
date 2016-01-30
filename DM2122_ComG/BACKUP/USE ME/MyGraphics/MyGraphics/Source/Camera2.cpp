#include "Camera2.h"
#include "Application.h"
#include "Mtx44.h"
#include <iostream>
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
	static const float CAMERA_SPEED = 50.f;
    if (Application::IsKeyPressed(VK_LEFT) )
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
	if(Application::IsKeyPressed(VK_UP))
	{
		
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
        if (view.y < 0.93){
            float pitch = (float)(-CAMERA_SPEED * dt);
            rotation.SetToRotation(-pitch, right.x, right.y, right.z);
            view = rotation * view;
            target = position + view;
            
       }
        std::cout << "UP" << view.y << std::endl;
	}
	if(Application::IsKeyPressed(VK_DOWN))
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

        std::cout <<"DOWN"<< up << std::endl;
	}
	if(Application::IsKeyPressed('W'))
	{
		Vector3 direction = target - position;
		
			Vector3 view = (target - position).Normalized();
			position += view * (float)(20.f * dt);
            target += view * (float)(20.f * dt);
		
	}
	if(Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * (float)(20.f * dt);
        target -= view * (float)(20.f * dt);
	}
    if (Application::IsKeyPressed('A'))
    {
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        position -= right * (float)(20.f * dt);
        target -= right * (float)(20.f * dt);
    }
    if (Application::IsKeyPressed('D'))
    {
        Vector3 view = (target - position).Normalized();
        Vector3 right = view.Cross(up);
        position += right * (float)(20.f * dt);
        target += right * (float)(20.f * dt);
    }
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera2::Reset()
{
	//position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}