/*
 * Vecteur3.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Vector3.h"
#include <cmath> // sqrt ()

Vector3::Vector3(double x, double y, double z) {
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;

}

Vector3::~Vector3() {
	// TODO Auto-generated destructor stub
}

Vector3 Vector3::operator*(Vector3 v) const {
	Vector3 strechedVector = Vector3(coords[0]*v[0],coords[1]*v[1],coords[2]*v[2]);

	return strechedVector;
}

Vector3 Vector3::operator*(double s) const {
	Vector3 strechedVector = Vector3(coords[0]*s,coords[1]*s,coords[2]*s);

	return strechedVector;
}
void Vector3::operator*=(double s) {
	coords[0]*=s;
	coords[1]*=s;
	coords[2]*=s;

}

Vector3 Vector3::operator+(Vector3 v) const {
	Vector3 addedVector = Vector3(coords[0] + v.coords[0],coords[1] + v.coords[1],coords[2] + v.coords[2]);

	return addedVector;
}

void Vector3::operator+=(Vector3 v) {
	coords[0]+=v.coords[0];
	coords[1]+=v.coords[1];
	coords[2]+=v.coords[2];
}

Vector3 Vector3::operator-(Vector3 v) const {
	Vector3 addedVector = Vector3(coords[0] - v.coords[0],coords[1] - v.coords[1],coords[2] - v.coords[2]);

	return addedVector;
}
void Vector3::operator-=(Vector3 v) {
	coords[0]-=v.coords[0];
	coords[1]-=v.coords[1];
	coords[2]-=v.coords[2];
}

double Vector3::norm () const
{
	return sqrt ( coords[0]*coords[0] + coords[1]*coords[1] + coords[2]*coords[2] );
}

Vector3 Vector3::normalized ()
{
	Vector3 res;
	double ni = 1.0 / norm ();
	res[0] *= ni;
	res[1] *= ni;
	res[2] *= ni;
	return res;
}

void Vector3::normalize ()
{
	double ni = 1.0 / norm ();
	coords[0] *= ni;
	coords[1] *= ni;
	coords[2] *= ni;
}

double& Vector3::operator[] ( const int& i )
{
	return coords[i];
}


