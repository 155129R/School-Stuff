#ifndef _LIGHT_H
#define _LIGHT_H

#include "Vertex.h"




struct Light{

    Position position;
    Color color;
    float power;
    float kC, kL, kQ;

    //Construtor
    Light::Light(){
        position = (0.f, 0.f, 0.f);
        color = (1.0f, 1.0f, 1.0f);
        power = 1.f;
        kC = kL = kQ = 1.f;

    };




};







#endif // !_LIGHT_H
