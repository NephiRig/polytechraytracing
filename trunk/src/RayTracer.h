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
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"
#include "Rectangle.h"
#include "Scene.h"
#include "LightSource.h"
#include "PhongModel.h"
#include "Color.h"


class RayTracer {
public:
	/*RayTracer(Scene s =0, LightModel _lm =0);*/
	RayTracer(const Set<Shape*> &sp, PhongModel &_lm =0 );
	virtual ~RayTracer();

	virtual void raytrace(Image* img);
private:
	/*Scene scene;*/

	virtual Color calculateColor(Ray &r, int recursions);
	virtual bool isHidden(LightSource lightSource, Vector3 point);

	PhongModel lm;
	Set<Shape*> shapes;
	LightSource light[2];
	int l_length;

};

#endif /* RAYTRACER_H_ */
