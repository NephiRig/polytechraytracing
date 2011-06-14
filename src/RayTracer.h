/*
 * RayTracer.h
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#ifndef RAYTRACER_H_
#define RAYTRACER_H_

#include <iostream>
#include <fstream> // ofstream
#include "Vector3.h"
#include "Screen.h"
#include "ScreenV2.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "Rectangle.h"
#include "Scene.h"
#include "LightSource.h"
#include "PhongModel.h"
#include "Color.h"

const double PI = 3.141592;


class RayTracer {
public:

	Scene scene;
	PhongModel lm;

	RayTracer(Scene &sc , PhongModel &_lm );
	virtual ~RayTracer();
	virtual void raytrace(Image* img);

private:
	virtual Color calculateColor(Ray &r, int recursions);
	virtual bool isHidden(LightSource* &lightSource, Vector3 &point);

	int NB_OF_INTERATIONS;


};

#endif /* RAYTRACER_H_ */
