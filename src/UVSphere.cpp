/*
 * UVSphere.cpp
 *
 *  Created on: 12 juin 2011
 *      Author: michelet
 */

#include "UVSphere.h"
#include <cmath>

UVSphere::UVSphere(const Vector3 &center, float radius, Texture *tex) :
	_center(center), _radius(radius), _tex(tex) {
}

UVSphere::~UVSphere() {
	// TODO Auto-generated destructor stub
}

Set<double> UVSphere::intersect(const Ray& r) const {
	Set<double> s = Set<double> (2);

	Vector3 temp = r.get_origin() - _center;

	double a = dot_product(r.get_direction(), r.get_direction());
	double b = 2 * dot_product(r.get_direction(), temp);
	double c = dot_product(temp, temp) - _radius * _radius;

	double delta = b * b - 4.0 * a * c;

	if (delta > 0.0) {
		delta = sqrt(delta);

		double t1 = (-b - delta) / (2 * a);
		double t2 = (-b + delta) / (2 * a);

		s.add(t1);
		if (t2 != t1) {
			s.add(t2);
		}

	}
	return s;
}


Vector3 UVSphere::normal(const Vector3& pt_intersect) const {
	return (pt_intersect - _center).normalize();
}


bool UVSphere::hit(const Ray &r, float tmin, float tmax, float time, HitRecord *record) const {
	Vector3 temp = r.get_origin() - _center;

	double a = dot_product(r.get_direction(), r.get_direction());
	double b = 2 * dot_product(r.get_direction(), temp);
	double c = dot_product(temp, temp) - _radius * _radius;

	double delta = b * b - 4.0 * a * c;

	if (delta > 0.0) {
		delta = sqrt(delta);
		double t = (- b - delta) / (2.0 * a);

		if (t < tmin) {
			t = (- b + delta) / (2.0 * a);
		}
		if (t < tmin || t > tmax) {
			return false;
		}

		record->t = t;
		record->hit_p = (r.get_origin() + t * r.get_direction());
		Vector3 n = record->normal = (record->hit_p - _center) / _radius;

		float twopi = 6.28318530718f;
		float theta = acos(n[2]);
		float phi = atan2(n[1], n[0]);

		if (phi < 0.0f) {
			phi += twopi;
		}

		float one_over_2pi = .159154943092f;
		float one_over_pi = .318309886184f;
		record->uv = Vector2(phi * one_over_2pi, (M_PI - theta) * one_over_pi);

		record->hit_tex = _tex;
		return true;
	}
	return false;
}

bool UVSphere::shadowHit(const Ray &r, float tmin, float tmax, float time) const {
	Vector3 temp = r.get_origin() - _center;

	double a = dot_product(r.get_direction(), r.get_direction());
	double b = 2 * dot_product(r.get_direction(), temp);
	double c = dot_product(temp, temp) - _radius * _radius;

	double delta = b * b - 4.0 * a * c;

	if (delta > 0.0) {
		delta = sqrt(delta);
		double t = (- b - delta) / (2.0 * a);

		if (t < tmin) {
			t = (- b + delta) / (2.0 * a);
		}
		if (t < tmin || t > tmax) {
			return false;
		}

		return true;
	}
	return false;
}
