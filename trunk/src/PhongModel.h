/*
 * PhongModel.h
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 *
 */

#ifndef PHONGMODEL_H_
#define PHONGMODEL_H_

#include "LightModel.h"

/*
 * See http://en.wikipedia.org/wiki/Phong_reflection_model for more information
 */
class PhongModel : public LightModel{
public:
	PhongModel();
	virtual ~PhongModel();

	virtual double getAmbient() const;
	virtual double getDiffuse(Ray &normal, LightSource &source) const;
	virtual double getSpecular(Ray &refracted, LightSource &source) const;
private:
	double k_a;
	double k_d;
	double k_s;
	double n_s;
};

#endif /* PHONGMODEL_H_ */
