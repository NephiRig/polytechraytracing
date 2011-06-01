/*
 * Forme.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include "Vector3.h"
#include "Ray.h"
//#include "Intersection.h"
#include "Set.h"

class Intersection;

class Shape {
public:
	Shape();
	virtual ~Shape();
	// Material material;
	// virtual Vector3 normal ( const Vector3& pt  ) const = 0;
	// virtual Set<Vector3> intersect ( const Ray& r ) const = 0;
};

#endif /* SHAPE_H_ */
