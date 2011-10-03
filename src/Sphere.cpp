#include "Sphere.h"
#include <cmath>

Sphere::Sphere(const Color &color, const Material &material, const Vector3 &center, double radius) :
	_center(center), _radius(radius) {
	this->_color = color;
	this->_material = material;
}

Sphere::~Sphere() {
}

void Sphere::setMaterial(const Material &material) {
	_material = material;
}

Set<double> Sphere::intersect(const Ray& ray) const {

	Set<double> s = Set<double> (2);
	Vector3 d_o_x = dot_product(ray.getDirection(), (ray.getOrigin() - _center));
	Vector3 o_c = dot_product(ray.getOrigin(), _center);

	double a = ray.getDirection().norm() * ray.getDirection().norm();
	double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);
	double c = pow(_center.norm(), 2) + pow(ray.getOrigin().norm(), 2) - 2 * (o_c[0] + o_c[1] + o_c[2]) - _radius * _radius;

	//Apply solve function (-b +- sqrt(b^2-4ac))/2a
	double d = b * b - 4 * a * c; //the term in the root

	if (d > 0) { //We have an intersection
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);
		if (t1 < t2) {
			if (t1 > 0) {
				s.add(t1);
				s.add(t2);
			}
		} else if (t2 > 0) {
			s.add(t2);
		}
	}
	return s;
}

Vector3 Sphere::normal(const Vector3& pointIntersection) const {
	return (pointIntersection - _center);
}
