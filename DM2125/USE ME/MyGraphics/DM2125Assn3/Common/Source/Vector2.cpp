#include "Vector2.h"

Vector2::Vector2( float a, float b )
:x(a), y(b)
{
}

Vector2::Vector2( const Vector2 &rhs )
{
    this->x = rhs.x;
    this->y = rhs.y;
}

void Vector2::Set( float a, float b )
{
    x = a;
    y = b;
}

Vector2 Vector2::operator+( const Vector2& rhs ) const
{
    return Vector2((this->x + rhs.x), (this->y + rhs.y));
}

Vector2 Vector2::operator-( const Vector2& rhs ) const
{
    return Vector2((this->x - rhs.x), (this->y - rhs.y));
}

Vector2 Vector2::operator-( void ) const
{
	return Vector2(this->x*-1,this->y*-1);
}

Vector2 Vector2::operator*( float scalar ) const
{
	return Vector2((this->x*scalar),(this->y*scalar));
}

float Vector2::Length( void ) const
{
	return sqrt(pow((this->x),2)+pow((this->y),2));
}

float Vector2::Dot( const Vector2& rhs ) const
{
	return ((this->x * rhs.x)+(this->y * rhs.y));
}

Vector2 Vector2::Normalized( void )
{
    
    return Vector2((this->x / sqrt(pow((this->x), 2) + pow((this->y), 2))), (this->y / sqrt(pow((this->x), 2) + pow((this->y), 2))));
}
