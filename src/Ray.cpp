/*
 * Rayon.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim, Michelet Valentin
 */

#include "Ray.h"

Ray::Ray(const Vector3 &origin, const Vector3 &direction) {
	coords[0] = origin;
	coords[1] = direction;
}

Ray::Ray(const Ray &r) {
	*this = r;
}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}


Vector3 Ray::get_origin() const {
	return coords[0];
}

Vector3 Ray::get_direction() const {
	return coords[1];
}

void Ray::set_origin(const Vector3 &new_origin) {
	coords[0] = new_origin;
}

void Ray::set_direction(const Vector3 &new_direction) {
	coords[1] = new_direction;
}


Vector3 Ray::getPoint(double t) const {
	return coords[0] + (t * coords[1]);
}


Vector3 Ray::operator[](int i) const {
	return coords[i];
}

Vector3& Ray::operator[](const int &i) {
	return coords[i];
}


std::ostream& operator<<(std::ostream &os, const Ray &r) {
	return os << r.get_origin() << " + t*" << r.get_direction() << std::endl;
}
