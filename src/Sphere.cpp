/*
 * Sphere.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Sphere.h"
#include "math.h"
#include <iostream>
using namespace std;

Sphere::Sphere(Vector3 _centre, double _radius) :
	centre(_centre), radius(_radius) {
}


/*
 *	Calculate the first intersection of a ray with a spehere
 */
Vector3 Sphere::intersect(const Ray r) {

	double a = r.ptD.norm();

	Vector3 d_o_x = r.ptD*(r.ptO-centre);
	double b = 2*(d_o_x[0]+d_o_x[1]+d_o_x[2]);
	cout << " a=";
	cout << a;
	cout << " b=";
	cout << b;

	Vector3 o_c = r.ptO*centre;
	//TODO real function for pow
	double c = centre.norm()*centre.norm()
			+ r.ptO.norm()*r.ptO.norm()
			- 2*(o_c[0]+o_c[1]+o_c[2])
			- radius*radius;

	cout << " c=";
	cout << c;

	//Apply solve function (-b +- sqrt(b^2-4ac))/2a
	double d= b*b - 4*a*c; //the term in the root

	if(d < 0) { //We have no intersection
		return Vector3(0,0,0); //FIXME return specific null value
	} else {
		//FIXME: In a first step we only care about the smaller t (i.e. the first intersection)
		double t = (- b - sqrt(d))/(2*a);
		cout << " t=";
		cout << t;
		return r.getPoint(t);
	}
}

Sphere::~Sphere() {
	// TODO Auto-generated destructor stub
}
