#pragma once
#include "Object.h"


class CHeart: public CObject
{
private:
	// przechowuje ilosc punktow zycia
	int zdrowie, maxzdrowie;
	//stan okresla tryb serca czerwony lub niebieski
	int stan;
	//The velocity of the heart
	int mVelX, mVelY;
	
public:
	

	CHeart(int x, int y,int MZ,int S): CObject(x,y)
	{
		x_pos = x;
		y_pos = y;
		maxzdrowie = MZ;
		zdrowie = MZ;
		stan = S;
		mVelX = 0;
		mVelY = 0;
	}

	static const int Heart_WIDTH = 24;
	static const int Heart_HEIGHT = 24;

	static const int Heart_VEL = 4;
	
	void handleEvent( SDL_Event& e );
	void move();
	void Render();

	int getZdrowie();
	void akt_zdrowie(int zmiana);
	void akt_poz(int x, int y);
	int getMaxzdrowie();
	int getStan();
	int getH();
	int getW();

};
