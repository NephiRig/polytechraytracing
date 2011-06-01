/*
 * Vecteur3.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim, Michelet Valentin
 */

#include "Vector3.h"
#include <cmath> // sqrt ()

Vector3::Vector3(double x, double y, double z) {
	coords[0] = x;
	coords[1] = y;
	coords[2] = z;
}

Vector3::Vector3(const Vector &v1) {
	*this = v1;
}

Vector3::~Vector3() {
	// TODO Auto-generated destructor stub
}


double Vector3::get_x() const {
	return coords[0];
}

double Vector3::get_y() const {
	return coords[1];
}

double Vector3::get_z() const {
	return coords[2];
}


void Vector3::set_x(double x) {
	coords[0] = x;
}

void Vector3::set_y(double y) {
	coords[1] = y;
}

void Vector3::set_z(double z) {
	coords[2] = z;
}


double operator[](int i) const {
	return coords[i];
}

double& operator[](int i) {
	return coords[i];
}


bool operator==(const Vector3 &v1, const Vector3 &v2) {
	return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}

bool operator!=(const Vector3 &v1, const Vector3 &v2) {
	return !(v1 == v2);
}


const Vector3& Vector3::operator+() const {
	return *this;
}

Vector3 Vector3::operator-() const {
	return Vector3(-coords[0], -coords[1], -coords[2]);
}


Vector3& operator=(const Vector3 &v) {
	coords[0] = v[0];
	coords[1] = v[1];
	coords[2] = v[2];
}


Vector3 operator*(const Vector3& v, const double k) const {
	return Vector3(v[0] * k, v[1] * k, v[2] * k);
}

Vector3 operator*(const double k, const Vector3& v) const {
	return Vector3(v[0] * k, v[1] * k, v[2] * k);
}

Vector3 operator/(const double k, const Vector3& v) {
	return Vector3(v[0] / k, v[1] / k, v[2] / k);
}

Vector3 operator+(const Vector3& v1, const Vector3& v2) const {
	return Vector3(v1[0] + v2[0], v1[1] + v2[1], v1[2] + v2[2]);
}

Vector3 operator-(const Vector3& v1, const Vector3& v2) const {
	return Vector3(v1[0] - v2[0], v1[1] - v2[1], v1[2] - v2[2]);
}


Vector3& Vector3::operator*=(const double k) {
	return *this = (*this * k);
}

Vector3& Vector3::operator/=(const double k) {
	return *this = (*this / k);
}

Vector3& Vector3::operator+=(const Vector3& v) {
	return *this = (*this + v);
}

Vector3& Vector3::operator-=(const Vector3& v) {
	return *this = (*this - v);
}


double dot_product(const Vector3& v1, const Vector3& v2) const {
	return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

Vector3 cross_product(const Vector3& v1, const Vector3& v2) const {
	return Vector3(
			v1[1] * v2[2] - v1[2] * v2[1],
			v1[2] * v2[0] - v1[0] * v2[2],
			v1[0] * v2[1] - v1[1] * v2[0]
	);
}


double Vector3::norm() const {
	return sqrt(coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
}

double Vector3::squared_norm() const {
	return (coords[0] * coords[0] + coords[1] * coords[1] + coords[2] * coords[2]);
}

void Vector3::make_unit_vector() {
	*this = *this / (*this).norm();
}


double Vector3::min_coord() const {
	double tmp = coords[0];
	if (tmp > coords[1]) tmp = coords[1];
	if (tmp > coords[2]) tmp = coords[2];
	return tmp;
}

double Vector3::max_coord() const {
	double tmp = coords[0];
	if (tmp < coords[1]) tmp = coords[1];
	if (tmp < coords[2]) tmp = coords[2];
	return tmp;
}

double Vector3::min_abs_coord() const{
	double tmp = fabs(coords[0]);
	if (tmp > fabs(coords[1])) tmp = fabs(coords[1]);
	if (tmp > fabs(coords[2])) tmp = fabs(coords[2]);
	return tmp;
}

double Vector3::max_abs_coord() const{
	double tmp = fabs(coords[0]);
	if (tmp < fabs(coords[1])) tmp = fabs(coords[1]);
	if (tmp < fabs(coords[2])) tmp = fabs(coords[2]);
	return tmp;
}

int Vector3::index_min_coord() const {
	int index = 0;
	double tmp = coords[0];
	if (tmp > coords[1]) {
		tmp = coords[1];
		index = 1;
	}
	if (tmp > coords[2]) index = 2;
	return index;
}

int Vector3::index_max_coord() const {
	int index = 0;
	double tmp = coords[0];
	if (tmp < coords[1]) {
		tmp = coords[1];
		index = 1;
	}
	if (tmp < coords[2]) index = 2;
	return index;
}

int Vector3::index_min_abs_coord() const {
	int index = 0;
	double tmp = fabs(coords[0]);
	if (tmp > fabs(coords[1])) {
		tmp = fabs(coords[1]);
		index = 1;
	}
	if (tmp > fabs(coords[2])) index = 2;
	return index;
}

int Vector3::index_min_abs_coord() const {
	int index = 0;
	double tmp = fabs(coords[0]);
	if (tmp < fabs(coords[1])) {
		tmp = fabs(coords[1]);
		index = 1;
	}
	if (tmp < fabs(coords[2])) index = 2;
	return index;
}
