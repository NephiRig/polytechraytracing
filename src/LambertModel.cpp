/*
 * LambertModel.cpp
 *
 *  Created on: 07.06.2011
 *      Author: nb-gyglim
 */

#include "LambertModel.h"
#include  <cmath>

LambertModel::LambertModel() {
	k_a=0.2;
	k_d=0.8;

}

LambertModel::~LambertModel() {
	// TODO Auto-generated destructor stub
}


double LambertModel::getAmbient() const {
	return k_a;
}
double LambertModel::getDiffuse(Ray normal, LightSource source) const {
	Vector3 intersect_lightSource = source.position-normal.get_origin();
	double a_times_b = dot_product(normal.get_direction().normalize(),intersect_lightSource.normalize());
	//cout << "diff_light: " << a_times_b << "\n";
	if (a_times_b > 0) {
		return a_times_b*k_d;
	} else {
		return 0;
	}
}
double LambertModel::getSpecular(Ray refracted, LightSource source) const {
	return 0;
}

