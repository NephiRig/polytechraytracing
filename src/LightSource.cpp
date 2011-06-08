/*
 * LightSource.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "LightSource.h"

LightSource::LightSource(double intens, Vector3 pos, Color c) {
	intensity = intens;
	position = pos;
	if (c != 0){
		color = c;
	} else {
		color = Color(1,1,1);
	}

}

LightSource::~LightSource() {
	// TODO Auto-generated destructor stub
}
