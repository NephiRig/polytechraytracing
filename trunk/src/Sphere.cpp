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

/*
 *	Calculate the intersections of a ray with a sphere
 */
Set<Vector3> Sphere::intersect(const Ray& r) const {

	Set<Vector3> s = Set<Vector3> (2);

	double a = r.get_direction().norm() * r.get_direction().norm();

	Vector3 d_o_x = dot_product(r.get_direction(),(r.get_origin() - centre));
	double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);

	Vector3 o_c = dot_product(r.get_origin(),centre);
	//TODO real function for pow
	double c = centre.norm() * centre.norm() + r.get_origin().norm() * r.get_origin().norm() - 2
			* (o_c[0] + o_c[1] + o_c[2]) - radius * radius;


	//Apply solve function (-b +- sqrt(b^2-4ac))/2a
	double d = b * b - 4 * a * c; //the term in the root


	if (d < 0) { //We have no intersection
	} else {
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);
		/*cout << " t1=";
		cout << t1;
		cout << " t2=";
		cout << t2;*/

		s.add(r.getPoint(t1));
		if (t2 != t1) {
			s.add(r.getPoint(t2));
		}
	}
	return s;
}

Vector3 Sphere::normal(const Vector3& pt_intersect) const {
	return (centre - pt_intersect).normalize();
}
