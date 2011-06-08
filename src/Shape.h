/*
 * Shape.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
//#include "Intersection.h"
#include "Set.h"
#include "Color.h"

class Intersection;

struct HitRecord {
	float t;
	Vector3 normal;
	Color color;
};

class Shape {
public:
	Color color;

	Shape();
	virtual ~Shape();

	// Material material;

	virtual Vector3 normal(const Vector3& pt);
	virtual Set<Vector3> intersect(const Ray& r);

	virtual Color get_color(const Vector3& pt);
};

#endif /* SHAPE_H_ */
