/*
 * Rectangle.cpp
 *
 *  Created on: 15 juin 2011
 *      Author: michelet
 */

#include "Rectangle.h"
#include <cmath>
#include <iostream>

using namespace std;

Rectangle::Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width) :
	Plane(color, material, normAndPoint), _height(height), _width(width) {
}

Rectangle::~Rectangle() {
	// TODO Auto-generated destructor stub
}

Set<double> Rectangle::intersect(const Ray& r) const {
	Set<double> res = Set<double>(1);
	double t = (_d - _normAndPoint[1][0]*r[0][0] - _normAndPoint[1][1]*r[0][1] - _normAndPoint[1][2]*r[0][2])/(_normAndPoint[1][0]*r[1][0] + _normAndPoint[1][1]*r[1][1] + _normAndPoint[1][2]*r[1][2]);

	Vector3 inter = r.getPoint(t);
	if ((fabs(inter[0]-_normAndPoint[0][0]) < _width/2.0 && fabs(inter[2]-_normAndPoint[0][2]) < _height/2.0) && t > 0) {
		res.add(t);
		//cout << t << " " << r.getPoint(t) << endl;
	}
	return res;
}
