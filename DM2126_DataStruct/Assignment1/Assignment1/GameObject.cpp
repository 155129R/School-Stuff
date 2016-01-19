#include "GameObject.h"

#include <iostream>

int GameObject::count = 0;

GameObject::~GameObject()
{
    std::cout << "GameObject was destroyed." << std::endl; //For Testing
    --count;
}

GameObject::GameObject(const string& objectName)
:kName(objectName)
{

    std::cout << "GameObject was instantiated. With the objectName: " << objectName << std::endl; //For Testing
    std::cout << "GameObject was instantiated. With the kName: " << kName << std::endl; //For Testing
    count++;
}

int GameObject::getCount()
{
    return count;
}

string GameObject::getName(void)
{
    return this->kName;
}