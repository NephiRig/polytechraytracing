/*
 * Forme.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Shape.h"

Shape::Shape() {
	// TODO Auto-generated constructor stub
}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

Set<Vector3> Shape::intersect(const Ray& r) {
	return Set<Vector3>(0);
}
Vector3 Shape::normal(const Vector3& pt) {
	return Vector3(0,0,0);
}

Color Shape::get_color(const Vector3& pt) {
	return color;
}
