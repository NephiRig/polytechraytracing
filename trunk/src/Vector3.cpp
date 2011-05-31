/*
 * Vecteur3.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Vector3.h"

Vector3::Vector3(double x, double y, double z) {
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;

}

Vector3 Vector3::operator*(double s) {
	Vector3 strechedVector = Vector3(coords[0]*s,coords[1]*s,coords[2]*s);

	return strechedVector;
}
void Vector3::operator*=(double s) {
	coords[0]*=s;
	coords[1]*=s;
	coords[2]*=s;

}

Vector3 Vector3::operator+(Vector3 v) {
	Vector3 addedVector = Vector3(coords[0] + v.coords[0],coords[1] + v.coords[1],coords[2] + v.coords[2]);

	return addedVector;
}

void Vector3::operator+=(Vector3 v) {
	coords[0]+=v.coords[0];
	coords[1]+=v.coords[1];
	coords[2]+=v.coords[2];
}

Vector3 Vector3::operator-(Vector3 v) {
	Vector3 addedVector = Vector3(coords[0] - v.coords[0],coords[1] - v.coords[1],coords[2] - v.coords[2]);

	return addedVector;
}
void Vector3::operator-=(Vector3 v) {
	coords[0]-=v.coords[0];
	coords[1]-=v.coords[1];
	coords[2]-=v.coords[2];
}


Vector3::~Vector3() {
	// TODO Auto-generated destructor stub
}
