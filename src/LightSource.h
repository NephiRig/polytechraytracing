/*
 * LightSource.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "Vector3.h"
#include "Color.h"

class LightSource {
public:
	LightSource(double intens , Vector3 &pos , Color &c) ;
	virtual ~LightSource();

	double intensity;
	Color color;
	Vector3 position;
};

#endif /* LIGHTSOURCE_H_ */
