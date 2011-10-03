#include "Shape.h"

Shape::Shape() {
}

Shape::~Shape() {
}

Set<double> Shape::intersect(const Ray& r) const {
	return Set<double>(0);
}

Vector3 Shape::normal(const Vector3& pt) const {
	return Vector3(0,0,0);
}

Color Shape::getColor(const Vector3& pt) {
	return _color;
}
