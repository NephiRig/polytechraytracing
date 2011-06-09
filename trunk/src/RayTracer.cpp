/*
 * RayTracer.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "RayTracer.h"
#include <iostream>

using namespace std;

/*RayTracer::RayTracer(Scene s, LightModel _lm) {
 scene = s;
 lm = _lm;

 }*/

RayTracer::RayTracer(const Set<Shape*> &sp, PhongModel &_lm) {
	lm = _lm;
	shapes = sp;
}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}

/**
 * TODO: - Iterate over all the pixels of the screen
 *		 - Call calculateColor
 */
void RayTracer::raytrace(Image* img) {
	cerr << "Number of shapes:" << shapes.length();

	//Width and height of the image
	int w = img->width();
	int h = img->height();

	//The observer point
	Vector3 obs(0, 200, 0.0);

	// The aimed point
	Vector3 aimedPoint(0, 0, 200);

	//Distance to the screen from the observer point
	double distScreen = 350.0;

	//With the given values we create an according screen
	Screen s = Screen(obs, aimedPoint, distScreen, double(w), double(h));


	//A lightSource
	LightSource source1 = LightSource(0.5, Vector3(70, 70, 80), Color(1, 1, 0.5));
	LightSource source2 = LightSource(0.5, Vector3(-70, -70, 60), Color(1, 1, 1));
	light[0] = source1;
	light[1] = source2;

	//Iterate over all the pixels of the screen/image
	int count = 0;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			count++;
			//Create the ray from the observer point, passing through the pixel
			Ray r = Ray(obs, s.getPixel(x, y) - obs);

			//Set the pixel accoring to the calculated Color/Light
			img->setPixel(x, y, calculateColor(r, 15));
			cout << count << "; ";
		}

	}
	cout << "done";
}

/**
 * TODO: Implement Algorithm given on P65 of the Script
 * 		 (With the discussed modifications)
 */
Color RayTracer::calculateColor(Ray &r, int recursions) {

	//FIXME Initialize with the background color
	Color c = Color(0, 0, 0);

	//Get the first intersection with any shape
	Shape* closestShape = shapes.get(0);
	double closestIP;
	bool hasIntersection = false;

	for (int i = 0; i < shapes.length(); i++) {
		Set<double> intersections = shapes.get(i)->intersect(r);

		if (!hasIntersection && !intersections.empty()) {
			closestShape = shapes.get(i);
			closestIP = intersections[0];
			hasIntersection = true;
		} else if (hasIntersection && intersections[0] < closestIP) {
			closestShape = shapes.get(i);
			closestIP = intersections[0];
			hasIntersection = true;

		}
	}

	//if there are any intersections
	if (hasIntersection) {
		//Get the Point of the first intersection
		Vector3 intersection = r.getPoint(closestIP);

		//The normal at the point of intersection
		Vector3 n = closestShape->normal(intersection);

		//Make sure the normal points into the right direction
		if (dot_product(r.get_direction(), n) < 0) {
			n = -n;
		}
		Ray normal = Ray(intersection, n);

		//The reflected ray at the point of intersection
		//FIXME Move to the shape class, as it is the same for all the shapes
		Ray reflected =
				Ray(
						intersection,
						2 * n * (dot_product(n, r.get_direction()))
								- r.get_direction());

		/*
		 * Calculate the light compartments using the lightmodel
		 */

		//Ambient color
		//FIXME: Take L_a of scene instead of 1
		c = 1 * closestShape->material.k_a * closestShape->color;

		for (int i = 0; i < l_length; i++) {
			LightSource l = light[i];
			if (!isHidden(l, intersection)) {
				double diffuse = lm.getDiffuse(normal, l);
				double specular = lm.getSpecular(reflected, l);
				c += closestShape->material.k_d * diffuse  * closestShape->color * l.intensity;
				c += closestShape->material.k_s * specular * l.color             * l.intensity;
			}
		}

		//Recursive call
		if (recursions > 0) {
			//FIXME Define factor (in material for example: reflectiv index...)
			c += 0.5*calculateColor(reflected, --recursions);
		}
	}
	return c;
}

/**
 * TODO: Implement Algorithm to test, weather there are objects inbetween a point
 * 		 and our lightsource
 */
bool RayTracer::isHidden(LightSource lightSource, Vector3 point) {
	//TODO Programm
	return false;
}

