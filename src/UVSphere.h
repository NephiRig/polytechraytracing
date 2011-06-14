/*
 * UVSphere.h
 *
 *  Created on: 12 juin 2011
 *      Author: michelet
 */

#ifndef UVSPHERE_H_
#define UVSPHERE_H_

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Texture.h"

class UVSphere : public Shape {
public:
	Vector3 _center;
	float _radius;
	Texture *_tex;

	UVSphere(const Vector3 &center, float radius, Texture *tex);
	virtual ~UVSphere();

	Set<double> intersect(const Ray& r) const;
	Vector3 normal(const Vector3& pt_intersect) const;

	bool hit(const Ray &r, float tmin, float tmax, float time, HitRecord *record) const;
	bool shadowHit(const Ray &r, float tmin, float tmax, float time) const;

};

#endif /* UVSPHERE_H_ */
