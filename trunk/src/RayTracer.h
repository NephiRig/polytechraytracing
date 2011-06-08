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

#include "LambertModel.h"
#include "PhongModel.h"
#include "Color.h"


class RayTracer {
public:
	RayTracer();
	virtual ~RayTracer();

	virtual Image* raytrace();
};

#endif /* RAYTRACER_H_ */
