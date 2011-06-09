/*
 * Material.cpp
 *
 *  Created on: 01.06.2011
 *      Author: nb-gyglim
 */

#include "Material.h"

Material::Material(double k_a, double k_d, double k_s, double n_s) {
	this->k_a = k_a;
	this->k_d = k_d;
	this->k_s = k_s;
	this->n_s = n_s;

}

Material::~Material() {
	// TODO Auto-generated destructor stub
}
