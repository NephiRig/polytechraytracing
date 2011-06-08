/*
 * Sphere.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin, Michelet Valentin
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"
#include "Material.h"
#include "Vector3.h"

class Sphere : public Shape {
public:
	Vector3 centre;
	double radius;

	Sphere (const Vector3 &_centre, double _radius, const Color &_color);
	virtual ~Sphere();

	Set<Vector3> intersect (const Ray& r) const;

	Vector3 normal (const Vector3& pt_intersect) const;
};

#endif /* SPHERE_H_ */
