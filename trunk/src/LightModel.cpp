/*
 * LightModel.cpp
 *
 *  Created on: 07.06.2011
 *      Author: nb-gyglim
 */

#include "LightModel.h"

LightModel::LightModel() {
	// TODO Auto-generated constructor stub

}

LightModel::~LightModel() {
	// TODO Auto-generated destructor stub
}

double LightModel::getAmbient() const {
	return 1;
}

double LightModel::getDiffuse(Ray &normal, LightSource* &source) const {
	return 0;
}

double LightModel::getSpecular(Ray &refracted, LightSource* &source) const {
	return 0;
}


