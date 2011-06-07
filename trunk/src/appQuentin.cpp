/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>
#include <fstream> // ofstream
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "Vector3.h"
#include "Screen.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"

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

	Vector3 obs(0.0, 0.0, 0.0);
	Vector3 aimedPoint(0.0, 10.0, 0.0);
	double distScreen = 2.0;
	int w = 500;
	int h = 500;
	Screen s = Screen(obs, aimedPoint, distScreen, double(w), double(h));
	Vector3 r;
	cerr << "avant construction: w" << w << ";h" << h << endl;
	Image img(w, h, Color(0.0, 0.0, 0.0));
	cerr << "apres construction: u" << w << ";h" << h << endl;
	cerr << "apres construction2: u" << w << ";h" << h << endl;

	/*
	 * CODE GYGLIM
	 * TEST: Intersect sample sphere
	 */
	Ray ray = Ray(Vector3(0, 0, 0), Vector3(1, 0, 10));
	Sphere sphere = Sphere(Vector3(0, 0, 250), 20, Color(255, 0, 0));
	Set<Vector3> ip = sphere.intersect(ray);
	cout << "Intersectionpoint: 1";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout << ip[0][2];

	cout << "Intersectionpoint: 2";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout << ip[0][2];

	// TODO: lancer le rayon
	cerr << "a" << endl;
	for (int y = 0; y < h; ++y)
	{
		for (int x = 0; x < w; ++x)
		{
			Ray r2 = Ray(obs, Vector3(x - w / 2, y - h / 2, 400) - obs);
			//img.setPixel ( x, y, Color(0.5,0.5,0.5) );
			Set<Vector3> intersections = sphere.intersect(r2);
			if (!intersections.empty())
			{
				img.setPixel(x, y, sphere.color);
			}
			else
			{
				img.setPixel(x, y, Color(0, 0, 0));
			}
		}
	}
	cerr << "b" << endl;
	ofstream myfile;
	myfile.open("img.ppm");
	cerr << "on tente le writePPM" << endl;
	img.writePPM(myfile);
	cerr << "fin du writePPM" << endl;
	//img.writePPM ( cerr );
	cerr << endl;
	myfile.close();


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
	/*
	 * END CODE GYGLIM
	 */

	//*/
	/*
	 //Valentin
	 Sphere sphere = Sphere(Vector3(250, 250, -1000), 150, Color(0.650, 0.152, 0));
	 for (int y = 0; y < h; ++y) {
	 for (int x = 0; x < w; ++x) {
	 Ray ray = Ray(Vector3(-1, 0, 0), Vector3(x, y, 0));
	 Set<Vector3> ip = sphere.intersect(ray);
	 if (sphere.intersect(ray, -1, 1))
	 for (int k = 0; k < ip.length(); k++)
	 cout << ip.get(k);
	 cout << endl;
	 img.setPixel(x, y, sphere.color);
	 }
	 }
	 ofstream myfile;
	 myfile.open("sphere.ppm");
	 img.writePPM(myfile);
	 myfile.close();
	 //*/
	return 0;
} // main ()
//*/
