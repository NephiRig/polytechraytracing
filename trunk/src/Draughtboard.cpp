/*
 * Draughtboard.cpp
 *
 *  Created on: 8 juin 2011
 *      Author: michelet
 */

#include "Draughtboard.h"
#include <cmath> //floor()
#include <iostream>

using namespace std;

//*
Draughtboard::Draughtboard(const Color &color, const Color &colorD, const Ray &normAndPoint, double length, double width, double caseSize) :
	_colorD(colorD), _normAndPoint(normAndPoint), _length(length), _width(width), _caseSize(caseSize) {
	this->color = color;
	//Calculs de la constante d dans l'équation du plan P:ax+by+cz=d
	_d = _normAndPoint.get_direction()[0] * _normAndPoint.get_origin()[0] + _normAndPoint.get_direction()[1] * _normAndPoint.get_origin()[1] + _normAndPoint.get_direction()[2] * _normAndPoint.get_origin()[2];
}

Draughtboard::~Draughtboard() {
	// TODO Auto-generated destructor stub
}

Set<double> Draughtboard::intersect(const Ray& r) const {
	Set<double> res = Set<double>();
	double t = (_d - _normAndPoint[1][0] * r[0][0] - _normAndPoint[1][1] * r[0][1] - _normAndPoint[1][2] * r[0][2]) / (r[1][0] + r[1][1] + r[1][2]);
	if (t > 0)
		res.add(t);
	return res;
}

Vector3 Draughtboard::normal(const Vector3& pt) const {
	return _normAndPoint[1];
}
//*
Color Draughtboard::get_color(const Vector3 &pt) {
	/*
	if ((int) floor((pt / _caseSize)[0]) % 2 == (int) floor((pt / _caseSize)[1]) % 2)
		return color;
	else//*/
	if (pt[0] > 0 && pt[1] > 0)
		return color;
	else
		return _colorD;
}
//*/
