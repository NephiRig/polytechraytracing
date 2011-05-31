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
	Vector2(double x = 0, double y = 0);
	virtual ~Vector2();

	Vector2 operator*(double s);
	Vector2 operator+(Vector2 v);

	//the 3 coordinates
	// [0] = x, [1] = y
	double coords[2];
};

#endif /* VECTEUR2_H_ */
