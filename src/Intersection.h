/*
 * Intersection.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Vector3.h"
#include "Shape.h"

class Intersection {
public:
	Vector3 pt;
	Shape* sh;
	Intersection(Vector3 _pt, Shape* _sh = 0);
	virtual ~Intersection();
};

#endif /* INTERSECTION_H_ */
