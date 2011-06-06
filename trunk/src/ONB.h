/*
 * ONB.h
 *
 *  Created on: 6 juin 2011
 *      Author: michelet
 */

#ifndef ONB_H_
#define ONB_H_

#include "Vector3.h"
#include <iostream>

using namespace std;

class ONB {
public:
	Vector3 U, V, W;

	ONB() {};
	ONB(const Vector3 &a, const Vector3 &b, const Vector3 &c);

	Vector3 get_u() const;
	Vector3 get_v() const;
	Vector3 get_w() const;

	void set(const Vector3 &a, const Vector3 &b, const Vector3 &c);

	void initFromU(const Vector3 &u);
	void initFromV(const Vector3 &v);
	void initFromW(const Vector3 &w);

	void initFromUV(const Vector3 &u, const Vector3 &v);
	void initFromVU(const Vector3 &v, const Vector3 &u);

	void initFromUW(const Vector3 &u, const Vector3 &w);
	void initFromWU(const Vector3 &w, const Vector3 &u);

	void initFromVW(const Vector3 &v, const Vector3 &w);
	void initFromWV(const Vector3 &w, const Vector3 &v);

	friend istream &operator>>(istream &is, ONB &onb);
	friend ostream &operator<<(ostream &os, const ONB &onb);

	friend bool operator==(const ONB &onb1, const ONB &onb2);

};
#endif /* ONB_H_ */
