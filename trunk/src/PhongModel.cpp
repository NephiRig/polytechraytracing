/*
 * PhongModel.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "PhongModel.h"
#include <cmath>

PhongModel::PhongModel() {
}

PhongModel::~PhongModel() {
	// TODO Auto-generated destructor stub
}

double PhongModel::getAmbient(Material &m) const {
	return m.k_a;
}
/*
 * Calculate the diffuse light. This depends on the angle between the normal and the
 * vector passing through a lightsource from the point of intersection)
 */
double PhongModel::getDiffuse(Ray &normal, LightSource* &source, Material &m) const {
	//Get the vector which passes from the point on the shape thourgh the lightsource
	Vector3 intersect_lightSource = source->position - normal.get_origin();

	//Calculate the cosine of the angle between the normal and the vector above
	//The diffuse light is defined by this quantity
	double a_times_b = dot_product(normal.get_direction().normalize(),intersect_lightSource.normalize());
	//double a_times_b = dot_product(normal.get_direction(),intersect_lightSource);
	//a_times_b /= ( normal.get_direction().norm () * intersect_lightSource.norm () );
	//the cosine is positive if our angle 0 <= alpha <= 180, i.e. the vector to the
	// lightsource is not on the other side of the shape
	if (a_times_b >= 0) {
		return a_times_b*m.k_d;
	} else { //The lightsource is behind the shape
		return 0;
	}
}

/*
 * Calculate the specular light. This light depends on the angle between
 * the reflected ray and the vector passing through a lightsource
 * (from the point of intersection)
 */
double PhongModel::getSpecular(Ray &refracted, LightSource* &source, Material &m) const {
	//Get the vector which passes from the point on the shape thourgh the lightsource
	Vector3 intersect_lightSource = source-> position - refracted.get_origin();


	//Calculate the cosine of the angle between the reflected ray and the vector above
	//The specular light is defined by this quantity
	double a_times_b = dot_product(refracted.get_direction().normalize(),intersect_lightSource.normalize());
	//double a_times_b = dot_product(refracted.get_direction(),intersect_lightSource);
	//a_times_b /= ( refracted.get_direction().norm () * intersect_lightSource.norm () );


	//the cosine is positive if our angle 0 <= alpha <= 180, i.e. the vector to the
	// lightsource is not on the other side of the shape
	if (a_times_b >= 0) {
		return pow(a_times_b,m.n_s)*m.k_s;
	} else { //The lightsource is behind the shape
		return 0;
	}
}

