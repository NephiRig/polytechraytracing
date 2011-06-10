/*
 * RayTracer.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "RayTracer.h"
#include <iostream>

using namespace std;

RayTracer::RayTracer(Scene &sc, PhongModel &_lm) {
	lm = _lm;
	scene = sc;
	NB_OF_INTERATIONS = 1;
	cout << "\n # of Shapes: " << scene.shapes.length();
	cout << "\n # of Lights: " << scene.lightSources.length() << "\n";

	for (int i = 0; i < scene.shapes.length(); i++) {
		Color c = scene.shapes.get(i)->color;
		cout << "Color " << i << " R: ";
		cout << c[0] << "; G: " << c[1] << "; B:" << c[2] << "\n";
	}
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

	//With the given values we create an according screen
	Screen s = Screen(scene.observer, scene.aimedPoint, scene.distScreen,
			double(w), double(h));

	//Iterate over all the pixels of the screen/image
	int count = 0;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			count++;
			//Create the ray from the observer point, passing through the pixel
			Ray r = Ray(scene.observer, s.getPixel(x, y) - scene.observer);

			//Set the pixel accoring to the calculated Color/Light
			img->setPixel(x, y, calculateColor(r, NB_OF_INTERATIONS));
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
	Shape* closestShape = scene.shapes.get(0);
	double closestIP;
	bool hasIntersection = false;

	Ray r_moved = Ray(r.getPoint(1),r.get_direction());
	for (int i = 0; i < scene.shapes.length(); i++) {
		Set<double> intersections = scene.shapes.get(i)->intersect(r_moved);

		if (!hasIntersection && !intersections.empty()) {
			closestShape = scene.shapes.get(i);
			cout << "t1: " << intersections[0] << " t2: " << intersections[1];
			closestIP = intersections[0];
			hasIntersection = true;
		} else if (hasIntersection && !intersections.empty() && intersections[0] < closestIP) {
			closestShape = scene.shapes.get(i);
			closestIP = intersections[0];
			cout << "t1: " << intersections[0] << " t2: " << intersections[1];
			hasIntersection = true;
		}

	}

	//if there are any intersections
	if (hasIntersection) {
		//Get the Point of the first intersection
		Vector3 intersection = r_moved.getPoint(closestIP); //P := intersection

		//The normal at the point of intersection
		Vector3 n = closestShape->normal(intersection);

		//Make sure the normal points into the right direction
		//FIXME is this correct??
		if (dot_product(-r.get_direction(), n) < 0) {
		//if (dot_product(V, n) < 0) {
			n = -n;
		}
		Ray normal = Ray(intersection, n);

		//The reflected ray at the point of intersection
		//FIXME Move to the shape class, as it is the same for all the shapes
		Ray reflected =
				Ray(intersection,
						2 * n * (dot_product(n, r.get_direction()))
								- r.get_direction());

		/*
		 * Calculate the light compartments using the lightmodel
		 */

		//Ambient color
		//FIXME: Take L_a of scene instead of 1
		c = 1 * closestShape->material.k_a * closestShape->color;

		for (int i = 0; i < scene.lightSources.length(); i++) {
			LightSource* l = scene.lightSources.get(i);
			if (!isHidden(l, intersection)) {

				double diffuse = lm.getDiffuse(normal, l);
				double specular = lm.getSpecular(reflected, l);
				c += closestShape->material.k_d * diffuse * closestShape->color
						* l->intensity;
				c += closestShape->material.k_s * specular * l->color
						* l->intensity;

			}
		}

		//Recursive call
		if (recursions > 0) {
			//FIXME Define factor (in material for example: reflectiv index...)
			c += 1 * calculateColor(reflected, --recursions);
		}
	}
	return c;
}

/**
 * TODO: Implement Algorithm to test, weather there are objects inbetween a point
 * 		 and our lightsource
 */
bool RayTracer::isHidden(LightSource* &lightSource, Vector3 &point) {

	//TODO Programm
	//Create the ray between intersection point and light source
	Ray r = Ray(point, (lightSource->position - point));

	//Get the first intersection with any shape
	Shape* closestShape = scene.shapes.get(0);
	double closestIP;
	bool hasIntersection = false;

/*
	for (int i = 0; i < scene.shapes.length(); i++) {
		Set<double> intersections = scene.shapes.get(i)->intersect(r);

		if (!hasIntersection && !intersections.empty()) {
			closestShape = scene.shapes.get(i);
			closestIP = intersections[0];
			hasIntersection = true;
		} else if (hasIntersection && !intersections.empty() && intersections[0] < closestIP) {
			closestShape = scene.shapes.get(i);
			closestIP = intersections[0];
			hasIntersection = true;

		}
	}

	//if there are any intersections
	if (hasIntersection) {
		//Get the Point of the first intersection
		Vector3 intersection = r.getPoint(closestIP);

		//Create a vector between the two object intersections
		Vector3 point_intersection = intersection - point;

		//Create a vector between object intersection and light source
		Vector3 point_light = lightSource->position - point;

		//If |point_light| > |point_intersection.norm| there is shadow
		cout << "true" << endl;
		return point_light.norm() > point_intersection.norm();
	}
*/
	return false;
}
