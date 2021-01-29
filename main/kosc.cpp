#include "kosc.h"

int CKosc::getTyp()
{
	return typ;
}

int CKosc::getObr()
{
	return obrazenia;
}

int CKosc::getX()
{
	return x_pos;
}

int CKosc::getY()
{
	return y_pos;
}

void CKosc::move()
{
    //Move the dot left or right
    x_pos += mVelX;

}
