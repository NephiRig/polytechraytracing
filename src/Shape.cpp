#include "Shape.h"

Shape::Shape() {
}

Shape::~Shape() {
}

Vector3 Shape::normal(const Vector3 &ptIntersect) const {
	return Vector3(0,0,0);
}

Set<double> Shape::ensIntersect(const Ray &rayon) const {
	return Set<double>(0);
}

Color Shape::getColor(const Vector3 &ptIntersect) const {
	return _color;
}

/*
Intersection Shape::getIntersectParams(const Ray &rayon) const {
	return Intersection(Set<double>(0), Vector3(0,0,0), _color);
}
//*/
