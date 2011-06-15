/*
 * LightModel.h
 *
 *  Created on: 07.06.2011
 *      Author: nb-gyglim
 */

#ifndef LIGHTMODEL_H_
#define LIGHTMODEL_H_

#include "Ray.h"
#include "LightSource.h"
#include "Material.h"

class LightModel {
public:
	LightModel();
	virtual ~LightModel();

	virtual double getAmbient(Material &m) const;
	virtual double getDiffuse(Ray &normal, LightSource* &source, Material &m) const;
	virtual double getSpecular(Ray &refracted, LightSource* &source, Material &m) const;
};

#endif /* LIGHTMODEL_H_ */
