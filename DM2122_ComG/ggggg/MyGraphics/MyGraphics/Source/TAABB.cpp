#include "TAABB.h"

TAABB::TAABB(const Vector3& min, const Vector3& max)
:m_vecMin(min), m_vecMax(max)
{

}
TAABB::~TAABB(){
    
}
bool PointInAABB(const TAABB& tBox, const Vector3& vecPoint)
{

    //Check if the point is less than max and greater than min
    if (vecPoint.x > tBox.m_vecMin.x && vecPoint.x < tBox.m_vecMax.x &&
        vecPoint.y > tBox.m_vecMin.y && vecPoint.y < tBox.m_vecMax.y &&
        vecPoint.z > tBox.m_vecMin.z && vecPoint.z < tBox.m_vecMax.z)
    {
        return true;
    }

    //If not, then return false
    return false;

}