/*
 * Sphere.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin, Michelet Valentin
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"
#include "Material.h"
#include "Vector3.h"

class Sphere : public Shape {
public:
	Vector3 _centre;
	double _radius;

	Sphere (const Color &color = 0, const Material &material = 0, const Vector3 &centre = 0, double radius = 0);
	virtual ~Sphere();

	Set<double> intersect (const Ray& r) const;
	Vector3 normal (const Vector3& pt_intersect) const;
	Color get_color(const Vector3 &pt);
};

#endif /* SPHERE_H_ */
