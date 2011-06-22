#include "Ray.h"

Ray::Ray(const Vector3 &origin, const Vector3 &direction) {
	coords[0] = origin;
	coords[1] = direction;
}

Ray::Ray(const Ray &r) {
	*this = r;
}

Ray::~Ray() {
}


Vector3 Ray::getOrigin() const {
	return coords[0];
}

Vector3 Ray::getDirection() const {
	return coords[1];
}

void Ray::setOrigin(const Vector3 &new_origin) {
	coords[0] = new_origin;
}

void Ray::setDirection(const Vector3 &new_direction) {
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


ostream& operator<<(ostream &os, const Ray &r) {
	return os << r.getOrigin() << " + t*" << r.getDirection() << std::endl;
}
