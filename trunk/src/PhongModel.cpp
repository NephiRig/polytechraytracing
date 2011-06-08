/*
 * PhongModel.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "PhongModel.h"
#include <cmath>

PhongModel::PhongModel() {
	k_a=0.05;
	k_d=0.45;
	k_s=0.8;
	n_s=20;

}

PhongModel::~PhongModel() {
	// TODO Auto-generated destructor stub
}

double PhongModel::getAmbient() const {
	return k_a;
}
double PhongModel::getDiffuse(Ray normal, LightSource source) const {
	Vector3 intersect_lightSource = source.position-normal.get_origin();
	double a_times_b = dot_product(normal.get_direction().normalize(),intersect_lightSource.normalize());
	if (a_times_b > 0) {
		return a_times_b*k_d;
	} else {
		return 0;
	}
}
double PhongModel::getSpecular(Ray refracted, LightSource source) const {
	Vector3 intersect_lightSource = source.position-refracted.get_origin();
	double a_times_b = -dot_product(refracted.get_direction().normalize(),intersect_lightSource.normalize());
	if (a_times_b > 0) {
		return pow(a_times_b,n_s)*k_s;
	} else {
		return 0;
	}
}

