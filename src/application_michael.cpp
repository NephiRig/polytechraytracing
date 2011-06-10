/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>
#include <fstream> // ofstream
#include "Vector3.h"
#include "Screen.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "Rectangle.h"
#include "RayTracer.h"
#include "PhongModel.h"
#include "Color.h"

using namespace std;

int main(int argc, char **argv) {
	cout << "start \n";
	//Scene scene = Scene();


	Set<Shape*> shapes = Set<Shape*>();

	//Create the shapes
	Sphere* sphere = new Sphere(Vector3(0, 20, 150), 20, Color(1, 0, 0));
	Sphere* sphere2 = new Sphere(Vector3(0, 20, 100), 20, Color(0.01, 0.01, 0.01));
	sphere2->material.k_a = 0.5;
	sphere2->material.k_d = 0.4;
	sphere2->material.k_s = 0.1;
	sphere2->material.n_s = 5;

	Sphere* sphere3 = new Sphere(Vector3(70, 70, 80), 4, Color(1, 1, 0));
	Sphere* sphere4 = new Sphere(Vector3(-70, -70, 80), 4, Color(1, 1, 1));


	shapes.add((Shape*)sphere);
	shapes.add((Shape*)sphere2);
	shapes.add((Shape*)sphere3);
	shapes.add((Shape*)sphere4);

	// light sources
	Vector3 position1 = Vector3(70, 70, 80);
	Color c1 =  Color(1, 1, 0.5);
	LightSource* source1 = new LightSource(1, position1, c1);

	Vector3 position2 = Vector3(-70, -70, 60);
	Color c2 = Color(1, 1, 1);
	LightSource* source2 = new LightSource(1, position2, c2);

	Set<LightSource*> lights = Set<LightSource*>();
	lights.add(source1);
	lights.add(source2);


	//The observer point
	Vector3 obs(0, 200, 0.0);

	// The aimed point
	Vector3 aimedPoint(0, 0, 200);

	//Distance to the screen from the observer point
	double distScreen = 350.0;

	Scene s = Scene(shapes,lights,obs,aimedPoint, distScreen);

	PhongModel lm = PhongModel();
	RayTracer rayTracer = RayTracer(s, lm);
	cout <<  "Raytrcer created \n";

	Image* img = new Image(500,500);
	rayTracer.raytrace(img);


	ofstream myfile;
	myfile.open("img11.ppm");
	cerr << "on tente le writePPM" << endl;
	img->writePPM(myfile);
	cerr << "fin du writePPM" << endl;
	cerr << endl;
	myfile.close();

	//Remove pointers
	delete(sphere);
	delete(sphere2);
	delete(sphere3);
	delete(sphere4);
	delete(source1);
	//delete(source2);
	delete(img);

	return 0;
}
