#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <iostream>
#include "Timer.h"

using namespace std;

class CObject
{
protected:
	// polozenie
	int x_pos, y_pos;


public:
	CObject(int x, int y);
	virtual void Render()
	{
		cout << "error" << endl;
	}


	int getX();
	int getY();

};


