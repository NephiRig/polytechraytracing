/*
 * Sphere.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin, Michelet Valentin
 */

#include "Sphere.h"
#include "math.h"
#include <iostream>

using namespace std;

Sphere::Sphere(const Vector3 &_centre, double _radius, const Color &_color) :
	centre(_centre), radius(_radius), color(_color) {
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

bool Sphere::intersect(const Ray &r, float tmin, float tmax/*, HitRecord *record*/) const {
	/*Vector3 o_c = r[0] - centre;
	double a = dot_product(r[1], r[0]);
	double b = (dot_product(r[1], o_c));
	double c = dot_product(r[0] - centre, r[0] - centre);
	double d = b * b - a * c;

	if (d < 0) {
		double t = (-bp - sqrt(d)) / a;

		if (t < tmin)
			t = (-bp + sqrt(d)) / a;

		if (t < tmin || t > tmax)
			return false;
		/*
		record->t = t;
		record->normal = unitVector(r.ptO + t * r.ptD - centre);
		record->color = color;
		//*/
	/*
		return true;
	}//*/
	return false;
}

/*
 *	Calculate the intersections of a ray with a sphere
 */
Set<Vector3> Sphere::intersect(const Ray& r) const {

	Set<Vector3> s = Set<Vector3> (2);

	Vector3 o_c = r[0] - centre;
	double a = dot_product(r[1], r[0]);
	double b = 2 * (dot_product(r[1], o_c));
	//TODO real function for pow
	double c = dot_product(r[0] - centre, r[0] - centre);

	//Apply solve function (-b +- sqrt(b²-4ac))/2a
	double d = b * b - 4 * a * c; //the term in the root

	cout << a << " " << b << " " << c << " " << o_c << endl;

	if (d < 0) { //We have no intersection
		/*
		Vector3 null = Vector3(0, 0, 0);
		s.add(null); //FIXME return specific null value
		//*/
	} else {
		cout << d << endl;
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);
		s.add(r.getPoint(t1));
		if (t2 != t1) {
			s.add(r.getPoint(t2));
		}
	}
	return s;
}

Vector3 Sphere::normal(const Vector3& pt) const {
	return Vector3(0, 0, 0);
}
