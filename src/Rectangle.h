/*
 * Rectangle.h
 *
 *  Created on: 15 juin 2011
 *      Author: michelet
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Plane.h"

class Rectangle : public Plane {
public:
	double _height;
	double _width;

	Rectangle(const Color &color, const Material &material, const Ray &normAndPoint, double height, double width);
	virtual ~Rectangle();

	virtual Set<double> intersect(const Ray& r) const;
};

#endif /* RECTANGLE_H_ */
