#include "Object.h"

CObject::CObject(int x,int y)
{
	x_pos = x;
	y_pos = y;
}

int CObject::getX()
{
	return x_pos;
}

int CObject::getY()
{
	return y_pos;
}
