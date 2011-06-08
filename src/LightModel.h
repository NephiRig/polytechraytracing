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

class LightModel {
public:
	LightModel();
	virtual ~LightModel();

	virtual double getAmbient() const = 0;
	virtual double getDiffuse(Ray normal, LightSource source) const = 0;
	virtual double getSpecular(Ray refracted, LightSource source) const = 0;
};

#endif /* LIGHTMODEL_H_ */
