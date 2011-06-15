/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>
#include <fstream> // ofstream
#include <cstdio> // sprintf
/*
#ifdef _MSC_VER
   #include "stdint.h"
#else
   #include <cstdint>
#endif
*/
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Vector3.h"
#include "Sphere.h"
#include "Draughtboard.h"
#include "Ray.h"
#include "Image.h"
#include "RayTracer.h"
#include "Timer.h"

using namespace std;

//Screen attributes
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;

bool quit = false;
int mouse_clicked_x;
int mouse_clicked_y;
int mouse_pos_x;
int mouse_pos_y;
bool mouse_down = false;
RayTracer *rt = NULL;
Image *img = NULL;
SDL_Surface* screen = NULL;
double camera_t = 0.0;
Vector3 posSphere;
double rayonCamera = 1.0;
bool recordvideo = false;
int videoimages = 0;

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

void fillSurfaceFromFile ( SDL_Surface *surface, Image* img, const char* f )
{
	SDL_Surface *img_sdl = load_image ( f );
	apply_surface ( 0, 0, img_sdl, screen );
	SDL_FreeSurface ( img_sdl );
}
/*
void fillSurfaceNoFile(SDL_Surface *surface, Image* img)
{ // TODO: à terminer, ne marche pas pour l'instant
    int bpp = surface->format->BytesPerPixel;
    cerr << "bpp: " << bpp << endl;
    switch(bpp) {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16 *)p = pixel;
        break;
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
		/ *
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN) {
        	//for ( int y = 0; y < )
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }* /
    }
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
				//p2[0] = img->data[x][y][0];
				//p2[1] = img->data[x][y][1];
				//p2[2] = img->data[x][y][2];
				*p2 = 0;//img->data[x][y].getRGB ();
			}
		}
    }
        break;
    }
}
*/
void refreshDisplay ()
{
	ofstream myfile;
	char f[100] = "img.ppm";
	if ( recordvideo )
		sprintf ( f, "img%05d.ppm", ++videoimages );
	myfile.open( f );
	img->writePPM(myfile);
	myfile.close();

	//fillSurfaceNoFile ( screen, img );
	fillSurfaceFromFile ( screen, img, f );
	SDL_Flip( screen );
}

void handle_events(SDL_Event& event)
{
	bool refresh = false;
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
	else if ( event.type == SDL_KEYDOWN )
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE:
				quit = true;
			break;
			
			case SDLK_LEFT:
				rt->scene.observer[0] -= 10.0;
				refresh = true;
			break;

			case SDLK_RIGHT:
				rt->scene.observer[0] += 10.0;
				refresh = true;
			break;

			case SDLK_UP:
				rt->scene.observer[2] += 10.0;
				refresh = true;
			break;

			case SDLK_DOWN:
				rt->scene.observer[2] -= 10.0;
				refresh = true;
			break;

			case SDLK_d:
				camera_t -= .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene.observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene.observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				refresh = true;
			break;
			
			case SDLK_f:
			{
				int n = 100;
				recordvideo = true;
				for ( int i = 0; i < n; ++i )
				{
					cerr << "iteration " << i << " sur " << n << endl;
					camera_t -= .1;
					cerr << "camera_t: " << camera_t << endl;
					rt->scene.observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
					rt->scene.observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
					rt->raytrace ( img );
					refreshDisplay ();
				}
			}
			break;

			case SDLK_q:
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene.observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene.observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				refresh = true;
			break;
			
			case SDLK_w:
				camera_t -= 0.50;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene.aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene.aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				refresh = true;
			break;
			
			case SDLK_x:
				camera_t += 0.50;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene.aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene.aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				refresh = true;
			break;
			
			case SDLK_v:
				recordvideo = !recordvideo;
				cerr << "recordvideo: " << recordvideo << endl;
			break;

			default:
			break;
		}
	}

	if ( refresh == true )
	{
		rt->raytrace ( img );
		refreshDisplay ();
	}
}
/*
void dispUint32 ( uint32_t v )
{
	for ( int i = 31; i >= 0; --i )
		cerr << ((v & (1 << i)) >> i);
}
*/
int main(int argc, char **argv)
{
	cerr << "test huhu" << endl;
	
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
	SDL_WM_SetCaption("Polytech Ray Tracing", NULL);




	Set<Shape*> shapes = Set<Shape*> (); // create scene
	// shapes
	posSphere = Vector3 ( 0.0, 0.0, 20.0 );
	Sphere* sphere1 = new Sphere ( posSphere, 4.0, Color ( 0.0, 0.0, 1.0 ) );
	sphere1->material.k_a = 0.05;
	sphere1->material.k_d = 0.2;
	sphere1->material.k_s = 0.8;
	sphere1->material.n_s = 30;
	Sphere* sphere2 = new Sphere ( Vector3 ( 10.0, 0.0, 20.0 ), 4.0, Color ( 1.0, 0.0, 0.0 ) );
	sphere2->material.k_a = 0.05;
	sphere2->material.k_d = 0.2;
	sphere2->material.k_s = 0.8;
	sphere2->material.n_s = 30;
	Sphere* sphere3 = new Sphere ( Vector3 ( 0.0, 0.0, 30.0 ), 4.0, Color ( 0.0, 1.0, 0.0 ) );
	sphere2->material.k_a = 0.05;
	sphere2->material.k_d = 0.2;
	sphere2->material.k_s = 0.8;
	sphere2->material.n_s = 30;

	Draughtboard *damier1 = new Draughtboard(Color(0.1, 0.1, 0.1), Color(.7, .7, .7), Ray(Vector3(10, -4, 20), Vector3(0, 1, 0)), 40, 40, 5);
	damier1->material.k_a = 0.05;
	damier1->material.k_d = 0.10;
	damier1->material.k_s = 0.01;
	damier1->material.n_s = 5;
	damier1->material.k_reflex=0.08;

	//sphere3->material.k_a = 0.2;
	shapes.add ( sphere1 );
	shapes.add ( sphere2 );
	shapes.add ( sphere3 );
	shapes.add ( damier1 );
	// light sources
	Set<LightSource*> lights = Set<LightSource*> ();
	Vector3 posLight1 = Vector3 ( 0.0, 10.0, 20.0 );
	Vector3 posLight2 = Vector3 ( 20.0, 0.0, 20.0 );
	LightSource* source1 = new LightSource ( 1.0, posLight1, Color ( 1.0, 1.0, 0.5 ) );
	LightSource* source2 = new LightSource ( 15.0, posLight2, Color ( 1.0, 1.0, 1.0 ) );
	lights.add ( source1 );
	lights.add ( source2 );
	//Sphere* sphere4 = new Sphere ( posLight1, 2.0, Color ( 1.0, 1.0, 0.5 ) );
	//Sphere* sphere5 = new Sphere ( posLight2, 0.5, Color ( 1.0, 1.0, 1.0 ) );
	//shapes.add ( (Shape*)sphere4 );
	//shapes.add ( (Shape*)sphere5 );

	Vector3 obs ( 0.0, 0.0, -20.0 );
	rayonCamera = (obs - posSphere).norm ();
	cerr << "rayon camera : " << rayonCamera << endl;

	Vector3 aimedPoint = posSphere;
	double distScreen = 0.50; //700.0; // distance to the screen from the observer point
	Vector3 wayUp = Vector3 ( 0.0, 1.0, 0.0 );
	Scene s = Scene ( &shapes, &lights, obs, wayUp, aimedPoint, distScreen );
	PhongModel lm = PhongModel ();
	rt = new RayTracer ( s, lm );

	img = new Image ( SCREEN_WIDTH, SCREEN_HEIGHT, Color ( 0.0, 0.0, 0.0 ) );

	rt->raytrace ( img );
	refreshDisplay ();


	Timer timer = Timer ();
	int fps = 35;







	// main loop
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
		
		if( timer.getTicks () < 1000 / fps )
			SDL_Delay ( ( 1000 / fps ) - timer.getTicks () );
	}
	SDL_FreeSurface ( screen );
	SDL_Quit ();
	
	delete sphere1;
	delete sphere2;
	delete sphere3;
	delete damier1;
	delete source1;
	delete source2;
	delete rt;
	delete img;

	return 0;
} // main ()

