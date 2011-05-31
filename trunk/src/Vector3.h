/*
 * Vecteur3.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#ifndef VECTEUR3_H_
#define VECTEUR3_H_

class Vector3 {
public:
	Vector3::Vector3(double x = 0, double y = 0, double z = 0);
	virtual ~Vector3();

	Vector3 operator*(double s);
	Vector3 operator+(Vector3 v);

	//the 3 coordinates
	// [0] = x, [1] = y, [2]=z
	double coords[3];
};

#endif /* VECTEUR3_H_ */
