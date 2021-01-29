#include "Heart.h"

int CHeart::getZdrowie()
{
	return zdrowie;
}

void CHeart::akt_zdrowie(int zmiana)
{
	zdrowie = zdrowie + zmiana;
}

int CHeart::getMaxzdrowie()
{
	return maxzdrowie;
}

int CHeart::getStan()
{
	return stan;
}


void CHeart::akt_poz(int x, int y)
{
	x_pos = x_pos + x;
	y_pos = y_pos + y;
}

void CHeart::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= Heart_VEL; break;
            case SDLK_DOWN: mVelY += Heart_VEL; break;
            case SDLK_LEFT: mVelX -= Heart_VEL; break;
            case SDLK_RIGHT: mVelX += Heart_VEL; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += Heart_VEL; break;
            case SDLK_DOWN: mVelY -= Heart_VEL; break;
            case SDLK_LEFT: mVelX += Heart_VEL; break;
            case SDLK_RIGHT: mVelX -= Heart_VEL; break;
        }
    }
}

void CHeart::move()
{
    //Move the dot left or right
    x_pos += mVelX;

    //If the dot went too far to the left or right
    if( ( x_pos < 1080/6 ) || ( x_pos + Heart_WIDTH > 1080*5/6 ) )
    {
        //Move back
        x_pos -= mVelX;
    }

    //Move the dot up or down
    y_pos += mVelY;

    //If the dot went too far up or down
    if( ( y_pos < 360 ) || ( y_pos + Heart_HEIGHT > 600 ) )
    {
        //Move back
       y_pos -= mVelY;
    }
}



