/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>
#include <fstream> // ofstream

#ifdef _MSC_VER
   #include "stdint.h"
#else
   #include <cstdint>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Vector3.h"
#include "Screen.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "RayTracer.h"

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

int mouse_clicked_x;
int mouse_clicked_y;
int mouse_pos_x;
int mouse_pos_y;
bool mouse_down = false;

SDL_Surface* screen = NULL;

SDL_Surface *
load_image(std::string filename)
{
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image using SDL_image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if (loadedImage != NULL)
	{
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	//Return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
{
	//Rectangle to hold the offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void fillSurfaceFromFile(SDL_Surface *surface, Image* img)
{
	SDL_Surface *img_sdl = load_image ( "img.ppm" );
	apply_surface ( 0, 0, img_sdl, screen );
	SDL_FreeSurface ( img_sdl );
}

void fillSurfaceNoFile(SDL_Surface *surface, Image* img)
{ // TODO: à terminer, ne marche pas pour l'instant
    int bpp = surface->format->BytesPerPixel;
    cerr << "bpp: " << bpp << endl;
    switch(bpp) {
    /*case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;
     */
    case 3:
    {
    	Uint8 *p = (Uint8 *)surface->pixels ;//+ y * surface->pitch + x * bpp;
    	Uint8 *p2;
    	for ( int y = 0; y < img->h; ++y )
    	{
    		for ( int x = 0; x < img->w; ++x )
    		{
    			p2 = p + y * surface->pitch + x * bpp;
    			p2[0] = img->data[x][y][0];
    			p2[1] = img->data[x][y][1];
    			p2[2] = img->data[x][y][2];
    		}
    	}
    }
        /*if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        	//for ( int y = 0; y < )
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }*/
        break;

    case 4:
    {
    	uint32_t *p = (uint32_t *)surface->pixels ;//+ y * surface->pitch + x * bpp;
    	uint32_t *p2;
        //*(Uint32 *)p = pixel;
    	for ( int y = 0; y < img->h - 1; ++y )
		{
			for ( int x = 0; x < img->w - 1; ++x )
			{
				cerr << "y:" << y << ";x:" << x << endl;
				p2 = p + y * surface->pitch + x * bpp;
				/*p2[0] = img->data[x][y][0];
				p2[1] = img->data[x][y][1];
				p2[2] = img->data[x][y][2];*/
				*p2 = 0;//img->data[x][y].getRGB ();
			}
		}
    }
        break;
    }
}

void handle_events(SDL_Event& event)
{
	// SDL_MOUSEMOTION
	// SDL_MOUSEBUTTONDOWN

	if (event.type == SDL_MOUSEMOTION)
	{
		if (mouse_down)
		{
			mouse_pos_x = event.button.x;
			mouse_pos_y = event.button.y;
			/*cout << "tracer rectangle de (" << mouse_clicked_x << ";"
			 << mouse_clicked_y << ") à (" << mouse_pos_x << ";"
			 << mouse_pos_y << ")" << endl;
			 apply_surface( 0, 0, hello, screen );
			 drawEmptyRect ( screen, mouse_clicked_x, mouse_clicked_y, mouse_pos_x,
			 mouse_pos_y, 255, 255, 255 );
			 SDL_Flip( screen );*/
		}
	}
	else if (event.type == SDL_MOUSEBUTTONDOWN)
	{
		//If the left mouse button was pressed
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			mouse_down = true;
			//Get the mouse offsets
			mouse_clicked_x = event.button.x;
			mouse_clicked_y = event.button.y;
		}
	}
	else if (event.type == SDL_MOUSEBUTTONUP)
	{
		if (event.button.button == SDL_BUTTON_LEFT)
		{
			mouse_down = false;
		}
	}
}
/*
void dispUint32 ( uint32_t v )
{
	for ( int i = 31; i >= 0; --i )
	{
		cerr << ((v & (1 << i)) >> i);
	}
}

int main (int argc, char **argv)
{
	Color c ( 0.0, 1.0, 0.0 );
	uint32_t res = 0;
	cerr << res << endl;
	res |= (int(c.val[0]*255) & 0xff) << 16;
	res |= (int(c.val[1]*255) & 0xff) << 8;
	res |= (int(c.val[2]*255) & 0xff);
	dispUint32 ( res );

}
*/
int main(int argc, char **argv)
{
	cerr << "test huhu" << endl;

	bool quit = false;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE); // w, h
	if (screen == NULL)
	{
		fprintf(stderr, "Unable to set video mode.");
		cerr << SDL_GetError() << endl;
		exit(1);
	}
	SDL_WM_SetCaption("kikou", NULL);

	int w = SCREEN_WIDTH;
	int h = SCREEN_HEIGHT;
	Image img(w, h, Color(0.0, 0.0, 0.0));
	//RayTracer rt = RayTracer ();
	//rt.raytrace(&img);

	ofstream myfile;
	myfile.open("img.ppm");
	cerr << "on tente le writePPM" << endl;
	img.writePPM(myfile);
	cerr << "fin du writePPM" << endl;
	//img.writePPM ( cerr );
	cerr << endl;
	myfile.close();

	//fillSurfaceNoFile ( screen, &img );
	fillSurfaceFromFile ( screen, &img );
	SDL_Flip( screen );


	//While the user hasn't quit
	while( quit == false )
	{
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
			handle_events ( event );
			if( event.type == SDL_QUIT )
			{
				//Quit the program
				quit = true;
			}
		}

		// la boucle
	}
	SDL_FreeSurface ( screen );
	SDL_Quit ();

	return 0;
} // main ()

