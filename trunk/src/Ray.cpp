/*
 * Rayon.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim, Michelet Valentin
 */

#include "Ray.h"

Ray::Ray(const Vector3 &p1, const Vector3 &p2) {
	ptO = p1;
	ptD = p2;
}

Ray::Ray(const Ray &r) {
	*this = r;
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}


Vector3 Ray::get_ptD() const {
	return ptD;
}

Vector3 Ray::get_ptO() const {
	return ptO;
}

void Ray::setptD(const Vector3 &v_ptD) {
	ptD = v_ptD;
}

void Ray::setptO(const Vector3 &v_ptO) {
	ptO = v_ptO;
}


Vector3 Ray::getPoint(double t) const {
	return ptO + (ptD * t);
}


ostream& operator<<(ostream &os, const Ray &v) {
	return os << v.get_ptO() << " + t*" << v.get_ptO() << endl;
}
