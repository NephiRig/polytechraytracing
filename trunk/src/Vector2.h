/*
 * Vecteur2.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#ifndef VECTEUR2_H_
#define VECTEUR2_H_

class Vector2 {
public:
	//the 2 coordinates
	// [0] = x, [1] = y
	double coords[2];

	Vector2(double x = 0, double y = 0);
	virtual ~Vector2();

	Vector2 operator*(double s);
	Vector2 operator+(Vector2 v);

	double norm();
	Vector2 normalized();
	void normalize();

	double& operator[] ( const int& i );
};

#endif /* VECTEUR2_H_ */
