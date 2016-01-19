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
        position = (0, 0, 0);
        color = (1, 1, 1);
        power = 1;
        kC = kL = kQ = 1;

    };




};







#endif // !_LIGHT_H
