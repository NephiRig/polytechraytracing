/*
 * ONB.cpp
 *
 *  Created on: 6 juin 2011
 *      Author: michelet
 */

#include "ONB.h"

#define ONB_EPSILON 0.01f

ONB::ONB(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
	U = a;
	V = b;
	W = c;
}

Vector3 ONB::get_u() const {
	return U;
}

Vector3 ONB::get_v() const {
	return V;
}

Vector3 ONB::get_w() const {
	return W;
}


void ONB::set(const Vector3 &a, const Vector3 &b, const Vector3 &c) {
	U = a;
	V = b;
	W = c;
}


void ONB::initFromU(const Vector3 &u) {
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	U = u.normalized();
	V = cross_product(U, n);
	if (V.norm() < ONB_EPSILON)
		V = cross_product(U, m);
	W = cross_product(U, V);
}

void ONB::initFromV(const Vector3 &v) {
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	V = v.normalized();
	U = cross_product(V, n);
	if (U.norm() < ONB_EPSILON)
		U = cross_product(V, m);
	W = cross_product(U, V);
}

void ONB::initFromW(const Vector3 &w) {
	Vector3 n(1.0f, 0.0f, 0.0f);
	Vector3 m(0.0f, 1.0f, 0.0f);
	W = w.normalized();
	U = cross_product(W, n);
	if (U.norm() < ONB_EPSILON)
		U = cross_product(W, m);
	V = cross_product(W, U);
}


void ONB::initFromUV(const Vector3 &u, const Vector3 &v) {
	U = u.normalized();
	W = (cross_product(u, v)).normalize();
	V = cross_product(W, U);
}

void ONB::initFromVU(const Vector3 &v, const Vector3 &u) {
	V = v.normalized();
	W = (cross_product(u, v)).normalize();
	U = cross_product(V, W);
}


void ONB::initFromUW(const Vector3 &u, const Vector3 &w) {
	U = u.normalized();
	V = (cross_product(w, u)).normalize();
	W = cross_product(U, V);
}

void ONB::initFromWU(const Vector3 &w, const Vector3 &u) {
	W = w.normalized();
	V = (cross_product(w, u)).normalize();
	U = cross_product(V, W);
}


void ONB::initFromVW(const Vector3 &v, const Vector3 &w) {
	V = v.normalized();
	U = (cross_product(v, w)).normalize();
	W = cross_product(U, V);
}

void ONB::initFromWV(const Vector3 &w, const Vector3 &v) {
	W = w.normalized();
	U = (cross_product(v, w)).normalize();
	V = cross_product(W, U);
}


istream &operator>>(istream &is, ONB &onb) {
	Vector3 new_u, new_v, new_w;
	is >> new_u >> new_v >> new_w;
	onb.initFromUV(new_u, new_v);
	return is;
}

ostream &operator<<(ostream &os, const ONB &onb) {
	return os << "(" << onb.get_u() << "; " << onb.get_v() << "; " << onb.get_w() << ")" << endl;
}


bool operator==(const ONB &onb1, const ONB &onb2) {
	return onb1.get_u() == onb2.get_u() && onb1.get_v() == onb2.get_v() && onb1.get_w() == onb2.get_w();
}
