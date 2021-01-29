#include "Object.h"
// positions - 12 #1 liczenie

class CBlaster: public CObject
{
protected:
	int position;
	int zwrot;
public:
	CBlaster(int x, int y, int pos, int zw): CObject(x,y)
	{
		x_pos= x;
		y_pos = y;
		position = pos;
		zwrot = zw;
	}
	int getX();
	int getY();
	int getZw();
	int getPos();


};

class Laser: public CBlaster
{
private:
	int obrazenia;
	int lWidth;
public:
	Laser(int x, int y, int pos, int zw, int obr, int lW): CBlaster(x,y,pos, zw)
	{
		x_pos = x;
		y_pos = y;
		position = pos;
		zwrot = zw;
		obrazenia = obr;
		lWidth = lW;
	}
	int getObr();
	int getlW();
};

