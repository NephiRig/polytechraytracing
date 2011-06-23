#include "UVSphere.h"
#include <cmath>

UVSphere::UVSphere(const Color &color, const Material &material, const Vector3 &center, float radius, Texture *tex) :
	_center(center), _radius(radius), _tex(tex) {
	this->_color = color;
	this->_material = material;
}

UVSphere::~UVSphere() {
}

Set<double> UVSphere::intersect(const Ray& r) const {

	Set<double> s = Set<double> (2);
	Vector3 d_o_x = dot_product(r.getDirection(), (r.getOrigin() - _center));
	Vector3 o_c = dot_product(r.getOrigin(), _center);

	double a = r.getDirection().norm() * r.getDirection().norm();
	double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);
	double c = pow(_center.norm(), 2) + pow(r.getOrigin().norm(), 2) - 2 * (o_c[0] + o_c[1] + o_c[2]) - _radius * _radius;

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


Vector3 UVSphere::normal(const Vector3& pt_intersect) const {
	return (pt_intersect - _center);
}


Color UVSphere::getColor(const Vector3& pt) {
	Vector3 n = normal(pt)/_radius;

	float twopi = 6.28318530718f;
	float theta = acos(n[2]);
	float phi = atan2(n[1], n[0]);

	if (phi < 0.0f) {
		phi += twopi;
	}

	float one_over_2pi = .159154943092f;
	float one_over_pi = .318309886184f;

	Vector2 uv(phi * one_over_2pi, (M_PI - theta) * one_over_pi);
	//cout << pt << endl;

	return _tex->value(uv, pt);
}
