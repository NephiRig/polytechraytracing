/*
 * Rayon.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim, Michelet Valentin
 */

#ifndef RAYON_H_
#define RAYON_H_

#include "Vector3.h"
#include <iostream>

using namespace std;

class Ray {

public:
	Vector3 ptD;
	Vector3 ptO;

	Ray(const Vector3 &v1 = Vector3(), const Vector3 &v2 = Vector3());
	Ray(const Ray &r);
	virtual ~Ray();

	Vector3 get_ptD() const;
	Vector3 get_ptO() const;

	void setptD(const Vector3 &v_ptD);
	void setptO(const Vector3 &v_ptO);

	/**
	 * \fn Vector3 getPoint(double t) const
	 * \brief Value in a point
	 *
	 * Calculates the point of the ray at parameter t
	 *
	 * \param t: the parameter
	 * \return the point of the ray at parameter t
	 */
	Vector3 getPoint(double t) const;

	friend ostream& operator<<(ostream &os, const Ray &v);
};

#endif /* RAYON_H_ */

