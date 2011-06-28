#include <iostream>
#include <fstream> // ofstream
#include <cstdio> // sprintf

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "RayTracer.h"
#include "SceneParser.h"
#include "Timer.h"

//Screen attributes
int SCREEN_WIDTH;
int SCREEN_HEIGHT;
int OVERSAMPLING;
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

		case SDLK_t: {
			int n = 100;
			recordvideo = true;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene._observer[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene._observer[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
		}
			break;

		case SDLK_l: {
			int n = 100;
			recordvideo = true;
			rt->scene._lightSources->get(0)->_position[1] = 10;
			for(int i = 0; i < n; ++i){
				cerr << "iteration " << i << " sur " << n << endl;
				camera_t += .1;
				cerr << "camera_t: " << camera_t << endl;
				rt->scene._lightSources->get(0)->_position[0] = posSphere[0] + cos(camera_t)*rayonCamera;
				rt->scene._lightSources->get(0)->_position[2] = posSphere[2] + sin(camera_t)*rayonCamera;
				rt->raytrace(img, OVERSAMPLING);
				refreshDisplay();
			}
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

int main(int argv, char** argc) {

	if (argv > 2) {
		std::cerr << "Please, enter a file name in argument or nothing to load the default scene." << std::endl;
		return -1;
	} else {
		//Scene Settups
		//If a file has been specified, we load it, otherwise, we load the default file defaultScene.xml
		SceneParser *parser;
		if (argv == 2) {
			parser = new SceneParser(argc[1]);
		} else {
			parser = new SceneParser((char*)"./SceneDescriptions/defaultScene.xml");
		}
		shapes = parser->_shapes;
		lights = parser->_lightSources;
		SCREEN_HEIGHT = parser->_screenHeight;
		SCREEN_WIDTH = parser->_screenWidth;
		OVERSAMPLING = parser->_oversampling;

		//FIXME faire une classe Camera qui regroupe les notions éparpillées dans ScreenV2 et Scene
		//		puis finir le parser pour initialiser la caméra comme il faut
		Vector3 obs(0.0, 0.0, -40.0);
		rayonCamera = (obs - posSphere).norm();
		cerr << "rayon camera : " << rayonCamera << endl;
		Vector3 aimedPoint = posSphere;
		double distScreen = 0.50; //700.0; // distance to the screen from the observer point
		Vector3 wayUp = Vector3(0.0, 1.0, 0.0);
		Scene s = Scene(&shapes, &lights, obs, wayUp, aimedPoint, distScreen);
		//FIN DU FIXME



		//SDL Setups
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



		//Picture creation
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
		return 0;
	}
}

int main1337(int argc, char **argv) {

	/*

	//Scene setup
	//Shapes
	posSphere = Vector3(0.0, 0.0, 0.0);

	ImageTexture *tex1 = new ImageTexture("./ImagesSRC/billard/billard1.ppm");
	ImageTexture *tex2 = new ImageTexture("./ImagesSRC/billard/billard2.ppm");
	ImageTexture *tex3 = new ImageTexture("./ImagesSRC/billard/billard3.ppm");
	ImageTexture *tex4 = new ImageTexture("./ImagesSRC/billard/billard4.ppm");
	ImageTexture *tex5 = new ImageTexture("./ImagesSRC/billard/billard5.ppm");
	ImageTexture *tex6 = new ImageTexture("./ImagesSRC/billard/billard6.ppm");
	ImageTexture *tex7 = new ImageTexture("./ImagesSRC/billard/billard7.ppm");
	ImageTexture *tex8 = new ImageTexture("./ImagesSRC/billard/billard8.ppm");
	ImageTexture *tex9 = new ImageTexture("./ImagesSRC/billard/billard9.ppm");
	ImageTexture *tex10 = new ImageTexture("./ImagesSRC/billard/billard10.ppm");
	ImageTexture *tex11 = new ImageTexture("./ImagesSRC/billard/billard11.ppm");
	ImageTexture *tex12 = new ImageTexture("./ImagesSRC/billard/billard12.ppm");
	ImageTexture *tex13 = new ImageTexture("./ImagesSRC/billard/billard13.ppm");
	ImageTexture *tex14 = new ImageTexture("./ImagesSRC/billard/billard14.ppm");
	ImageTexture *tex15 = new ImageTexture("./ImagesSRC/billard/billard15.ppm");

	Material boulMat = Material(0.2, 0.5, 0.4, 40, 0.2);

	UVSphere* sphere1 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(0, 0, 0), 2.0, tex1, M_PI/2.0, M_PI/2.0);
	UVSphere* sphere14 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(2, 0, 3), 2.0, tex14, 0.0, M_PI/2.0);
	UVSphere* sphere15 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-2, 0, 3), 2.0, tex15, 0.0, M_PI/2.0);
	UVSphere* sphere4 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(4, 0, 6), 2.0, tex4, 0.0, M_PI/2.0);
	UVSphere* sphere8 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(0, 0, 6), 2.0, tex8, 0.0, M_PI/2.0);
	UVSphere* sphere7 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-4, 0, 6), 2.0, tex7, 0.0, M_PI/2.0);
	UVSphere* sphere11 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(6, 0, 9), 2.0, tex11, 0.0, M_PI/2.0);
	UVSphere* sphere6 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(2, 0, 9), 2.0, tex6, 0.0, M_PI/2.0);
	UVSphere* sphere13 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-2, 0, 9), 2.0, tex13, 0.0, M_PI/2.0);
	UVSphere* sphere10 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-6, 0, 9), 2.0, tex10, 0.0, M_PI/2.0);
	UVSphere* sphere2 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(8, 0, 12), 2.0, tex2, 0.0, M_PI/2.0);
	UVSphere* sphere12 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(4, 0, 12), 2.0, tex12, 0.0, M_PI/2.0);
	UVSphere* sphere5 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-0, 0, 12), 2.0, tex5, 0.0, M_PI/2.0);
	UVSphere* sphere9 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-4, 0, 12), 2.0, tex9, 0.0, M_PI/2.0);
	UVSphere* sphere3 = new UVSphere(Color(0, 0, 0), boulMat, Vector3(-8, 0, 12), 2.0, tex3, 0.0, M_PI/2.0);

	Sphere* white = new Sphere(Color(1, 1, 1), boulMat, Vector3(0, 0, -18), 2.0);


	Rectangle *draughtboard1 = new Rectangle(Color(0.0, 100.0/255.0, 0.0), Material(0.01, 0.1, 0.1, 50, 0.0), Ray(Vector3(0, -2, 0), Vector3(0, 1, 0)), 60, 40);
	//*/


	/*
	ImageTexture *tex10 = new ImageTexture("./ImagesSRC/billard/billard10.ppm");
	UVSphere *sphere1 = new UVSphere(Color(0, 0, 0), Material(0.2, 0.9, 0.8, 80, 0.01), Vector3(-5, 0, 0), 4.0, tex10, M_PI/4.0, M_PI/4.0);

	NoiseTexture *noiseTex = new NoiseTexture(Color(166.0/255.0, 39.0/255.0, 0.0), Color(136.0/255.0, 29.0/255.0, 0.0), 2.0);
	UVSphere *sphere2 = new UVSphere(Color(0, 0, 0), Material(0.2, 0.9, 0.8, 80, 0.01), Vector3(5, 0, 0), 4.0, noiseTex);

	MarbleTexture *marbleTex = new MarbleTexture(0.10, 2);
	UVSphere *sphere3 = new UVSphere(Color(0, 0, 0), Material(0.2, 0.9, 0.8, 80, 0.01), Vector3(0, 0, 6), 4.0, marbleTex);

	//*/

	return 0;
} // main()
