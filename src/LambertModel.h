/*
 * LambertModel.h
 *
 *  Created on: 07.06.2011
 *      Author: nb-gyglim
 */

#ifndef LAMBERTMODEL_H_
#define LAMBERTMODEL_H_

#include "LightModel.h"

class LambertModel: public LightModel {
public:
	LambertModel();
	virtual ~LambertModel();

	virtual double getAmbient() const;
	virtual double getDiffuse(Ray normal, LightSource source) const;
	virtual double getSpecular(Ray refracted, LightSource source) const;
private:
	double k_a;
	double k_d;
};

#endif /* LAMBERTMODEL_H_ */
