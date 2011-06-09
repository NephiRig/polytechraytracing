/*
 * Forme.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Shape.h"
#include <iostream>

using namespace std;

Shape::Shape() {
	// TODO Auto-generated constructor stub
}

Shape::~Shape() {
	// TODO Auto-generated destructor stub
}

Set<double> Shape::intersect(const Ray& r) const {
	cerr << "ERROR, call of Shape intersect!";
	return Set<double>(0);
}
Vector3 Shape::normal(const Vector3& pt) const {
	return Vector3(0,0,0);
}

Color Shape::get_color(const Vector3& pt) {
	return color;
}
