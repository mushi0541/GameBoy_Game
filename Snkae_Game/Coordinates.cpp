#include "Coordinates.h"
Coordinates::Coordinates(int x, int y) :x(x), y(y) 
{
}

Coordinates::Coordinates(float x, float y) : x(x), y(y) 
{
}

void Coordinates::setX(float x) 
{
	this->x = x;
}
void Coordinates::setY(float y) 
{
	this->y = y;
}
float Coordinates::getX() 
{
	return this->x;
}
float Coordinates::getY() 
{
	return this->y;
}
