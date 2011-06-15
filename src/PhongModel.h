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

	virtual double getAmbient(Material &m) const;
	virtual double getDiffuse(Ray &normal, LightSource* &source, Material &m) const;
	virtual double getSpecular(Ray &refracted, LightSource* &source, Material &m) const;
};

#endif /* PHONGMODEL_H_ */
