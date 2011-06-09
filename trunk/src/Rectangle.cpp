/*
 * Rectangle.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "Rectangle.h"

Rectangle::Rectangle(int d, Vector3 n, Color col) {
	this->distance = d;
	this->n = n;
	this->color = col;

}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}



Set<double> Rectangle::intersect (const Ray& r) const {
	Vector3 d = r.get_direction();
	Vector3 source = r.get_direction();
	double t = distance/(dot_product(n,source)*(d[0]+d[1]+d[2]));

	/*Set<Vector3> s = Set<Vector3> (2);
	s.add(r.getPoint(t));
	return s;*/
}

Vector3 Rectangle::normal (const Vector3& pt_intersect) const {
	return n;
}
