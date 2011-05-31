/*
 * Sphere.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"

class Sphere : public Shape {
public:
	Vector3 centre;
	double radius;
	Sphere ( Vector3 _centre, double _radius );
	virtual ~Sphere();
};

#endif /* SPHERE_H_ */
