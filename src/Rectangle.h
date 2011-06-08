/*
 * Rectangle.h
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

class Rectangle  : public Shape {
public:
	Rectangle(int d=0, Vector3 n=0, Color col=0);
	virtual ~Rectangle();


	Set<Vector3> intersect (const Ray& r) const;

	Vector3 normal (const Vector3& pt_intersect) const;

private:
	int distance;
	Vector3 n;
};

#endif /* RECTANGLE_H_ */
