/*
 * PhongModel.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "PhongModel.h"
#include <cmath>

PhongModel::PhongModel() {
	k_a=1.0;//1;
	k_d=1;
	k_s=1;
	n_s=20;

}

PhongModel::~PhongModel() {
	// TODO Auto-generated destructor stub
}

double PhongModel::getAmbient() const {
	return k_a;
}
/*
 * Calculate the diffuse light. This depends on the angle between the normal and the
 * vector passing through a lightsource from the point of intersection)
 */
double PhongModel::getDiffuse(Ray &normal, LightSource* &source) const {
	//Get the vector which passes from the point on the shape thourgh the lightsource
	Vector3 intersect_lightSource = source->position - normal.get_origin();

	//Calculate the cosine of the angle between the normal and the vector above
	//The diffuse light is defined by this quantity
	double a_times_b = dot_product(normal.get_direction().normalize(),intersect_lightSource.normalize());

	//the cosine is positive if our angle 0 <= alpha <= 180, i.e. the vector to the
	// lightsource is not on the other side of the shape
	if (a_times_b > 0) {
		return a_times_b*k_d;
	} else { //The lightsource is behind the shape
		return 0;
	}
}

/*
 * Calculate the specular light. This light depends on the angle between
 * the reflected ray and the vector passing through a lightsource
 * (from the point of intersection)
 */
double PhongModel::getSpecular(Ray &refracted, LightSource* &source) const {
	//Get the vector which passes from the point on the shape thourgh the lightsource
	Vector3 intersect_lightSource = source-> position - refracted.get_origin();


	//Calculate the cosine of the angle between the reflected ray and the vector above
	//The specular light is defined by this quantity
	double a_times_b = dot_product(refracted.get_direction().normalize(),intersect_lightSource.normalize());


	//the cosine is positive if our angle 0 <= alpha <= 180, i.e. the vector to the
	// lightsource is not on the other side of the shape
	if (a_times_b > 0) {
		return pow(a_times_b,n_s)*k_s;
	} else { //The lightsource is behind the shape
		return 0;
	}
}

