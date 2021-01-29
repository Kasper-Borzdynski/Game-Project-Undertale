#include "Object.h"
#include "Heart.h"
#include "kosc.h"
#include "blaster.h"
#include "Timer.h"
#include <vector>

int stage = 0;

const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

CHeart frisk(SCREEN_WIDTH/2 - 10, SCREEN_HEIGHT*2/3, 92, 0);

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();


//The window we'll be rendering to
SDL_Window* gWindow = NULL;
//The window renderer
SDL_Renderer* gRenderer = NULL;


class RTexture
{
	public:
		//Initializes variables
		RTexture();

		//Deallocates memory
		~RTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );

		//Deallocates texture
		void free();

		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );

		//Gets image dimensions
		int getWidth();
		int getHeight();

		

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};


RTexture::RTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

RTexture::~RTexture()
{
	//Deallocate
	free();
}

bool RTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture

	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}
void RTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void RTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}
void RTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void RTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void RTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}
int RTexture::getWidth()
{
	return mWidth;
}

int RTexture::getHeight()
{
	return mHeight;
}

RTexture sans;
RTexture scena;
RTexture zaslona1,zaslona2;
RTexture blasterlewo, blasterprawo;
RTexture heart;
LTimer timer;
RTexture koscdluga;
RTexture kosckrotka;
vector<CKosc> atak1;


void CHeart::Render()
{
	heart.render(x_pos, y_pos);
}

void CKosc::Render()
{
	if(size==0)
	{
		kosckrotka.render(x_pos,y_pos);
		
	}
	if(size==1)
	{
		koscdluga.render(x_pos,y_pos);
	}

}



bool init()
{
		//Initialization flag
	bool success = true;

    //Initialize SDL
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Dunderdale", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

	if( !heart.loadFromFile( "heart.png" ) )
	{
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}

	if( !sans.loadFromFile( "sans.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	if( !scena.loadFromFile( "scena.png" ) )
	{
		printf( "Failed to load background texture image`!\n" );
		success = false;
	}
	if( !zaslona1.loadFromFile( "zaslona1.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !zaslona2.loadFromFile( "zaslona2.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !kosckrotka.loadFromFile( "kosckrotka.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !koscdluga.loadFromFile( "koscdluga.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !blasterlewo.loadFromFile( "blasterlewo.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	if( !blasterprawo.loadFromFile( "blasterprawo.png" ) )
	{
		printf( "Failed to load background texture image!\n" );
		success = false;
	}
	return success;
}

void close()
{
		//Free loaded images
	heart.free();
	sans.free();
	scena.free();
	zaslona1.free();
	zaslona2.free();
	kosckrotka.free();
	koscdluga.free();
	blasterlewo.free();
	blasterprawo.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e )!=0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					frisk.handleEvent(e);
					

				}
				timer.start();
					for(int i=0; i!=75; i=i+15)
					{
					CKosc dol(SCREEN_WIDTH/2-i, SCREEN_HEIGHT/2-i - 20 + 175, 3, 0, 1);
					atak1.push_back(dol);
					
					CKosc gora(SCREEN_WIDTH/2-i, SCREEN_HEIGHT/2-i + 10, 3, 0, 1);
					atak1.push_back(gora);
					
					CKosc prosto1(SCREEN_WIDTH/2-75-i, SCREEN_HEIGHT/2-75+50, 3, 0, 0);
					atak1.push_back(prosto1);
					
					CKosc prosto2(SCREEN_WIDTH/2-75-i, SCREEN_HEIGHT/2-75-20+175, 3 , 0, 1);
					atak1.push_back(prosto2);				
					}
				//move
				for(auto it=atak1.begin();it!=atak1.end();it++)
				{
					it->move();					
				}

				frisk.move();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );
				
				//render
				
				scena.render(0,0);
				sans.render( SCREEN_WIDTH/2 - 45, SCREEN_HEIGHT/5  );
				frisk.Render();


				for(auto it=atak1.begin();it!=atak1.end();it++)
				{
					it->Render();					
				}

				zaslona1.render(0,SCREEN_HEIGHT/2);
				zaslona2.render(180,600);
				zaslona1.render(900,SCREEN_HEIGHT/2);
				SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT/2, SCREEN_WIDTH *2/3, SCREEN_HEIGHT /3 };
				SDL_SetRenderDrawColor( gRenderer, 255, 255, 255, 0xFF );		
				SDL_RenderDrawRect( gRenderer, &outlineRect );

				//Update screen
				SDL_RenderPresent( gRenderer );
			
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}