#include "Object.h"

class CKosc: public CObject
{
private:
	int obrazenia;
	int typ;
	int size;

public:
	CKosc(int x, int y, int obr, int t, int s): CObject(x,y)
	{
		x_pos = x;
		y_pos = y;
		obrazenia = obr;
		typ = t;
		size = s;
		if(size == 0)
		{
		static const int kWidth = 15;
		static const int kHeight = 75;
		
		}
		if(size == 1)
		{
		static const int kWidth = 15;
		static const int kHeight = 48;
		
		}
	}

	static const int mVelX=6;

	int getTyp();
	int getObr();
	int getX();
	int getY();
	void Render();
	void move();
};
