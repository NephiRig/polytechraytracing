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

class Ray {

public:
	// coords[0] is the origin point of the vector
	// coords[1] is the vector's direction from its origin
	Vector3 coords[2];

	Ray(const Vector3 &origin = Vector3(), const Vector3 &direction = Vector3());
	Ray(const Ray &r);
	virtual ~Ray();

	Vector3 get_origin() const;
	Vector3 get_direction() const;

	void set_origin(const Vector3 &new_origin);
	void set_direction(const Vector3 &new_direction);

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

	Vector3 operator[](int i) const;
	Vector3& operator[](const int &i);

	friend std::ostream& operator<<(std::ostream &os, const Ray &r);
};

#endif /* RAYON_H_ */

