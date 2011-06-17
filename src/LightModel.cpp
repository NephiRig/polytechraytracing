#include "LightModel.h"

LightModel::LightModel() {
}

LightModel::~LightModel() {
}

double LightModel::getAmbient(Material &m) const {
	return 1.0;
}

double LightModel::getDiffuse(Ray &normal, LightSource* source, Material &m) const {
	return 0;
}

double LightModel::getSpecular(Ray &refracted, LightSource* source, Material &m) const {
	return 0;
}
