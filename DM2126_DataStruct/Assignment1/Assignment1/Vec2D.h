#ifndef VEC2D_H
#define VEC2D_H

struct Vec2D
{

public:

    Vec2D();    //[CONSTRUCTOR] Intialize instance of Vec2D class and instantiate member variables

    Vec2D(double xPos, double yPos); //[CONSTRUCTOR](Override) Intialize instance of Vec2D class and instantiate member variables and take in (x,y) values



    double x;

    double y;

};

#endif /*VEC2D_H*/