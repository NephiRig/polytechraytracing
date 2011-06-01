/*
 * Rayon.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#ifndef RAYON_H_
#define RAYON_H_

#include "Vector3.h"

class Ray {

public:
	Ray(Vector3 p1, Vector3 p2);
	virtual ~Ray();

	Vector3 getPoint(double t) const;

	Vector3 ptD;
	Vector3 ptO;
};

#endif /* RAYON_H_ */

