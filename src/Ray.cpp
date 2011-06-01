/*
 * Rayon.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Ray.h"


Ray::Ray(Vector3 p1, Vector3 p2) {
	ptO = p1;
	ptD = p2;

}

	//returns the point on the ray corresponding t
	Vector3 Ray::getPoint(double t) const {
		return ptO + (ptD*t);
	}

Ray::~Ray() {
	// TODO Auto-generated destructor stub
}
