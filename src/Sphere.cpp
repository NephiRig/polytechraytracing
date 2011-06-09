/*
 * Sphere.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin, Michelet Valentin, gyglim
 */

#include "Sphere.h"
#include "math.h"
#include <iostream>

using namespace std;

Sphere::Sphere(const Vector3 &_centre, double _radius, const Color &_color) :
	centre(_centre), radius(_radius) {
	this->color = _color;
	material=Material(0.1,0.4,0.5,20); //FIXME Take into constructor
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}

/*
 *	Calculate the intersections of a ray with a sphere
 */
Set<double> Sphere::intersect(const Ray& r) const {

	Set<double> s = Set<double> (2);

	double a = r.get_direction().norm() * r.get_direction().norm();

	Vector3 d_o_x = dot_product(r.get_direction(),(r.get_origin() - centre));
	double b = 2 * (d_o_x[0] + d_o_x[1] + d_o_x[2]);

	Vector3 o_c = dot_product(r.get_origin(),centre);

	double c = pow(centre.norm(),2) + pow(r.get_origin().norm(),2) - 2
			* (o_c[0] + o_c[1] + o_c[2]) - radius * radius;


	//Apply solve function (-b +- sqrt(b^2-4ac))/2a
	double d = b * b - 4 * a * c; //the term in the root


	if (d > 0) { //We have an intersection
		double t1 = (-b - sqrt(d)) / (2 * a);
		double t2 = (-b + sqrt(d)) / (2 * a);

		s.add(t1);
		if (t2 != t1) {
			s.add(t2);
		}
	}
	return s;
}

Vector3 Sphere::normal(const Vector3& pt_intersect) const {
	return (pt_intersect-centre).normalize();
}
