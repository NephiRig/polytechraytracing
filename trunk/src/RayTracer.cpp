/*
 * RayTracer.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "RayTracer.h"

RayTracer::RayTracer(Scene s) {
	scene = s;

}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

/**
 * TODO: - Iterate over all the pixels of the screen
 *		 - Call calculateColor
 */
void RayTracer::raytrace(Image* img) {

	//Width and height of the image
	int w = img->width();
	int h = img->height();

	//The observer point
	Vector3 obs(0, 0, 0.0);

	// The aimed point
	Vector3 aimedPoint(0, 0, 250.0);

	//Distance to the screen from the observer point
	double distScreen = 150.0;

	//With the given values we create an according screen
	Screen s = Screen(obs, aimedPoint, distScreen, double(w), double(h));

	//Create the shapes
	Sphere sphere = Sphere(Vector3(0, 0, 200), 100, Color(1, 0, 0));
	Sphere sphere2 = Sphere(Vector3(70, 70, 80), 2, Color(1, 1, 0.5));
	Rectangle rect = Rectangle(100, Vector3(1, 0, 0), Color(0, 0, 1));
	/*Set<Shape> shapes = Set<Shape> (3);
	 shapes.add(sphere);
	 shapes.add(sphere2);
	 shapes.add(rect);*/

	//A lightSource
	LightSource source = LightSource(1, Vector3(70, 70, 80), Color(1, 1, 0.5));

	//We use the Phong lightmodel
	PhongModel lm = PhongModel();

	//Iterate over all the pixels of the screen/image
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			//Create the ray from the observer point, passing through the pixel
			Ray r2 = Ray(obs, s.getPixel(x, y) - obs);

			//Get the intersections with a shape
			Set<Vector3> intersections = sphere.intersect(r2);

			//if there are any intersections
			if (!intersections.empty()) {
				//The normal at the point of intersection
				Vector3 n = sphere.normal(intersections[0]);
				Ray normal = Ray(intersections[0], n);

				//The reflected ray at the point of intersection
				//FIXME Move to the shape class, as it is the same for all the shapes
				Ray reflected = Ray(
						intersections[0],
						2 * n * dot_product(n, r2.get_direction())
								- r2.get_direction());

				//Calculate the light compartments using the lightmodel
				//TODO: Move the coefficients to the Material class of the Shape
				double ambient = lm.getAmbient();
				double diffuse = lm.getDiffuse(normal, source);
				double specular = lm.getSpecular(reflected, source);

				//Set the pixel accoring to the calculated Color/Light
				img->setPixel(x, y,
						ambient * sphere.color + diffuse * source.color + specular * source.color);
			} else {
				//TODO do we need the pixels without any intersection to BLACK?
				//img->setPixel(x, y, Color(0, 0, 0));
			}

			//Draw the lightSource sphere
			Set<Vector3> intersections2 = sphere2.intersect(r2);
			if (!intersections2.empty()) {
				img->setPixel(x, y, sphere2.color);
			}
		}
	}
}

/**
 * TODO: Implement Algorithm given on P65 of the Script
 * 		 (With the discussed modifications)
 */
Color RayTracer::calculateColor(Ray r, int recursions) {
	//TODO Programm
	return Color(0, 0, 0);
}

/**
 * TODO: Implement Algorithm to test, weather there are objects inbetween a point
 * 		 and our lightsource
 */
bool RayTracer::isHidden(LightSource lightSource, Vector3 point) {
	//TODO Programm
	return false;
}

