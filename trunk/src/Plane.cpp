/*
 * Plane.cpp
 *
 *  Created on: 14 juin 2011
 *      Author: michelet
 */

#include "Plane.h"
#include <cmath>

Plane::Plane(const Color &color, const Material &material, const Ray &normAndPoint) :
	_normAndPoint(normAndPoint) {
	this->_color = color;
	this->_material = material;//Material(0.1, 0.4, 0.5, 20,0.5); //FIXME Take into constructor
	//Calculs de la constante d dans l'équation du plan P:ax+by+cz=d
	_d = _normAndPoint[0][0] * _normAndPoint[1][0] + _normAndPoint[0][1] * _normAndPoint[1][1] + _normAndPoint[0][2] * _normAndPoint[1][2];
}

Plane::~Plane() {
	// TODO Auto-generated destructor stub
}

Set<double> Plane::intersect(const Ray& r) const {
	Set<double> res = Set<double>(1);
	double t = (_d - _normAndPoint[1][0]*r[0][0] - _normAndPoint[1][1]*r[0][1] - _normAndPoint[1][2]*r[0][2])/(_normAndPoint[1][0]*r[1][0] + _normAndPoint[1][1]*r[1][1] + _normAndPoint[1][2]*r[1][2]);

	if (t > 0) {
		res.add(t);
	}

	return res;
}

Vector3 Plane::normal(const Vector3& pt) const {
	return _normAndPoint[1];
}
