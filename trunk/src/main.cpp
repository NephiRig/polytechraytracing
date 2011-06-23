#include <iostream>
#include <fstream> // ofstream
#include <cstdio> // sprintf

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "Vector3.h"
#include "Sphere.h"
#include "Draughtboard.h"
#include "Ray.h"
#include "Image.h"
#include "RayTracer.h"
#include "UVSphere.h"
#include "ImageTexture.h"
#include "Timer.h"

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
Set<Shape*> shapes = Set<Shape*>();
Set<LightSource*> lights = Set<LightSource*>();
double rayonCamera = 1.0;
bool recordvideo = false;
int videoimages = 0;
int OVERSAMPLING = 1;


SDL_Surface *load_image(std::string filename) {
	//The image that's loaded
	SDL_Surface* loadedImage = NULL;

	//The optimized image that will be used
	SDL_Surface* optimizedImage = NULL;

	//Load the image using SDL_image
	loadedImage = IMG_Load(filename.c_str());

	//If the image loaded
	if(loadedImage != NULL) {
		//Create an optimized image
		optimizedImage = SDL_DisplayFormat(loadedImage);

		//Free the old image
		SDL_FreeSurface(loadedImage);
	}

	//Return the optimized image
	return optimizedImage;
}

void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination) {
	//Rectangle to hold the offsets
	SDL_Rect offset;

	//Get offsets
	offset.x = x;
	offset.y = y;

	//Blit the surface
	SDL_BlitSurface(source, NULL, destination, &offset);
}

void fillSurfaceFromFile(SDL_Surface *surface, Image* img, const char* f){
	SDL_Surface *img_sdl = load_image(f);
	apply_surface(0, 0, img_sdl, screen);
	SDL_FreeSurface(img_sdl);
}

void refreshDisplay() {
	char f[100] = "img.ppm";
	if(recordvideo) {
		sprintf(f, "img%05d.ppm", ++videoimages);
	}
	img->printImage(f);
	fillSurfaceFromFile(screen, img, f);
	SDL_Flip(screen);
}

void handle_events(SDL_Event& event) {
	bool refresh = false;

	if(event.type == SDL_MOUSEMOTION) {
		if(mouse_down) {
			mouse_pos_x = event.button.x;
			mouse_pos_y = event.button.y;
		}
	} else if(event.type == SDL_MOUSEBUTTONDOWN) {
		//If the left mouse button was pressed
		if(event.button.button == SDL_BUTTON_LEFT) {
			mouse_down = true;
			//Get the mouse offsets
			mouse_clicked_x = event.button.x;
			mouse_clicked_y = event.button.y;
		}
	} else if(event.type == SDL_MOUSEBUTTONUP) {
		if(event.button.button == SDL_BUTTON_LEFT) {
			mouse_down = false;
		}
	} else if(event.type == SDL_KEYDOWN){
		switch(event.key.keysym.sym) {
		case SDLK_ESCAPE:
			quit = true;
			break;

		case SDLK_LEFT:
			rt->scene._observer[0] -= 10.0;
			refresh = true;
			break;

		case SDLK_RIGHT:
			rt->scene._observer[0] += 10.0;
			refresh = true;
			break;

		case SDLK_UP:
			rt->scene._observer[2] += 10.0;
			refresh = true;
			break;

		case SDLK_DOWN:
			rt->scene._observer[2] -= 10.0;
			refresh = true;
			break;

		case SDLK_d:
			camera_t -= .1;
			cerr << "camera_t: " << camera_t << endl;
			rt->scene._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->scene._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = true;
			break;

		case SDLK_f: {
			int n = 100;
			recordvideo = true;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene._observer[1] = posSphere[1] + sin(camera_t)*rayonCamera;
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_l: {
			int n = 100;
			recordvideo = true;
			rt->scene._lightSources->get(1)->_position[1] = 10;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene._lightSources->get(1)->_position[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene._lightSources->get(1)->_position[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_m: {
			posSphere = Vector3(0.0, 0.0, 0.0);
			Sphere* spherem = new Sphere(Color(166.0/255.0, 39.0/255.0, 0.0), Material(0.2, 0.9, 0.8, 80, 0.4), posSphere, 4.0);
			Draughtboard *draughtboardm = new Draughtboard(Color(0.01, 0.01, 0.01), Material(0.4, 0.5, 0.4, 40, 0.5), Color(0.9, 0.9, 0.9), Ray(Vector3(0, -4, 0), Vector3(0, 1, 0)), 28, 24, 4);
			Vector3 posLightm = Vector3(-20.0, 20.0, -20.0);
			LightSource* sourcem = new LightSource(2.0, posLightm, Color(1.0, 1.0, 1.0));

			refreshDisplay();
			rt->scene._shapes->clear();
			rt->scene._shapes->add(spherem);
			rt->scene._shapes->add(draughtboardm);
			rt->scene._lightSources->add(sourcem);

			int n = 8;
			recordvideo = true;

			//Changing k_a, k_d and k_s values
			for(int k = 4; k <= n; k++) {
				for(int j = 4; j <= n; j++) {
					for(int i = 1; i <= 4; i++) {
						Material newMat(i/10.0, j/10.0, k/10.0, 70, 0.3);
						camera_t += .1;
						cerr << "camera_t: " << camera_t << endl;
						rt->scene._shapes->get(0)->_material = Material(newMat);
						rt->raytrace(img, OVERSAMPLING);
						refreshDisplay();
					}
				}
			}
			delete spherem;
			delete draughtboardm;
			delete sourcem;
		}
			break;

		case SDLK_q:
			camera_t += .1;
			cerr << "camera_t: " << camera_t << endl;
			rt->scene._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->scene._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = true;
			break;

		case SDLK_w:
			camera_t -= 0.50;
			cerr << "camera_t: " << camera_t << endl;
			rt->scene._aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->scene._aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
			refresh = true;
			break;

		case SDLK_x:
			camera_t += 0.50;
			cerr << "camera_t: " << camera_t << endl;
			rt->scene._aimedPoint[0] = posSphere[0] + cos(camera_t)*rayonCamera;
			rt->scene._aimedPoint[2] = posSphere[2] + sin(camera_t)*rayonCamera;
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

	if(refresh == true) {
		rt->raytrace(img, OVERSAMPLING);
		refreshDisplay();
	}
}

int main1337() {

	return 0;
}

int main(int argc, char **argv) {
	//SDL setup
	SDL_Event event;
	if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		fprintf(stderr, "Unable to init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	atexit(SDL_Quit);

	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE); // w, h
	if(screen == NULL) {
		fprintf(stderr, "Unable to set video mode.");
		cerr << SDL_GetError() << endl;
		exit(1);
	}
	SDL_WM_SetCaption("Polytech Ray Tracing", NULL);



	//Scene setup
	//Shapes
	posSphere = Vector3(0.0, 0.0, 0.0);
	ImageTexture *tex10 = new ImageTexture("./img/billard10.ppm");
	ImageTexture *tex8 = new ImageTexture("./img/billard8.ppm");
	//Sphere* sphere1 = new Sphere(Color(166.0/255.0, 39.0/255.0, 0.0), Material(0.2, 0.9, 0.8, 80, 0.4), Vector3(-5, 0, 0), 4.0);
	UVSphere* sphere1 = new UVSphere(Color(0, 0, 0), Material(0.2, 0.9, 0.8, 80, 0.01), Vector3(-5, 0, 0), 4.0, tex10);
	//Sphere* sphere2 = new Sphere(Color(38.0/255.0, 38.0/255.0, 38.0/255.0), Material(0.2, 0.9, 0.8, 80, 0.4), Vector3(5, 0, 0), 4.0);
	UVSphere* sphere2 = new UVSphere(Color(0, 0, 0), Material(0.2, 0.9, 0.8, 80, 0.01), Vector3(5, 0, 0), 4.0, tex8);
	//Draughtboard *draughtboard1 = new Draughtboard(Color(0.01, 0.01, 0.01), Material(0.4, 0.5, 0.4, 40, 0.5), Color(0.9, 0.9, 0.9), Ray(Vector3(0, -4, 0), Vector3(0, 1, 0)), 60, 40, 4);
	Rectangle* draughtboard1 = new Rectangle(Color(0.0, 100.0/255.0, 0.0), Material(0.4, 0.5, 0.4, 40, 0.0), Ray(Vector3(0, -4, 0), Vector3(0, 1, 0)), 60, 40);
	//Add shapes
	shapes.add(sphere1);
	shapes.add(sphere2);
	shapes.add(draughtboard1);

	//Light sources
	Vector3 posLight1 = Vector3(-20.0, 20.0, -20.0);
	LightSource* source1 = new LightSource(3.0, posLight1, Color(1.0, 1.0, 1.0));
	lights.add(source1);

	Vector3 obs(0.0, 0.0, -40.0);
	rayonCamera =(obs - posSphere).norm();
	cerr << "rayon camera : " << rayonCamera << endl;
	Vector3 aimedPoint = posSphere;
	double distScreen = 0.50; //700.0; // distance to the screen from the observer point
	Vector3 wayUp = Vector3(0.0, 1.0, 0.0);
	Scene s = Scene(&shapes, &lights, obs, wayUp, aimedPoint, distScreen);
	PhongModel lm = PhongModel();
	rt = new RayTracer(s, lm);

	img = new Image(SCREEN_WIDTH, SCREEN_HEIGHT, Color(0.0, 0.0, 0.0));

	rt->raytrace(img, OVERSAMPLING);
	refreshDisplay();

	nsUtil::Timer timer = nsUtil::Timer();
	int fps = 35;



	// main loop
	//While the user hasn't quit
	while(quit == false) {
		//While there's an event to handle
		while(SDL_PollEvent(&event)) {
			handle_events(event);
			if(event.type == SDL_QUIT) {
				//Quit the program
				quit = true;
			}
		}
		
		if(timer.getTicks() < 1000 / fps) {
			SDL_Delay((1000 / fps) - timer.getTicks());
		}
	}
	SDL_FreeSurface(screen);
	SDL_Quit();
	

	//Free memory
	delete sphere1;
	//delete sphere2;
	//delete draughtboard1;
	delete source1;
	delete rt;
	delete img;

	return 0;
} // main()
