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
#include "Color.h"

class Sphere : public Shape {
public:
	Vector3 centre;
	double radius;
	Color color;

	Sphere (const Vector3 &_centre, double _radius, const Color &_color);
	virtual ~Sphere();

	bool intersect(const Ray &r, float tmin, float tmax/*, HitRecord *record*/) const;

	Vector3 normal (const Vector3& pt) const;

	Set<Vector3> intersect ( const Ray& r ) const;
};

#endif /* SPHERE_H_ */
