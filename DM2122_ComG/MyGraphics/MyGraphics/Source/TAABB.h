#ifndef TAABB_H
#define TAABB_H

#include <Vector3.h>

struct TAABB
{
public:
    TAABB(const Vector3& min = (0.f,0.f,0.f), const Vector3& vecMax = (0.f,0.f,0.f));
    ~TAABB();

    Vector3 m_vecMax;
    Vector3 m_vecMin;

    
};

bool PointInAABB(const TAABB& tBox, const Vector3& vecPoint);
#endif /*TAABB_H*/