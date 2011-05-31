/*
 * Vecteur2.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Vector2.h"
#include <cmath> // sqrt ()

Vector2::Vector2(double x, double y) {
	coords[0] = x;
	coords[1] = y;
}

Vector2::~Vector2() {
	// TODO Auto-generated destructor stub
}

double Vector2::norm ()
{
	return sqrt ( coords[0]*coords[0] + coords[1]*coords[1] );
}

Vector2 Vector2::normalized ()
{
	Vector2 res;
	double ni = 1.0 / norm ();
	res[0] *= ni;
	res[1] *= ni;
	return res;
}

void Vector2::normalize ()
{
	double ni = 1.0 / norm ();
	coords[0] *= ni;
	coords[1] *= ni;
}

double& Vector2::operator[] ( const int& i )
{
	return coords[i];
}
