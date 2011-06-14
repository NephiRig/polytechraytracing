/*
 * Draughtboard.h
 *
 *  Created on: 8 juin 2011
 *      Author: michelet
 */

#ifndef DRAUGHTBOARD_H_
#define DRAUGHTBOARD_H_

#include "Color.h"
#include "Vector3.h"
#include "Shape.h"

//*
class Draughtboard: public Shape {
public:
	Color _colorD;
	Ray _normAndPoint;
	double _d;
	double _height;
	double _width;
	double _caseSize;

	Draughtboard() {};
	Draughtboard(const Color &color, const Color &colorD, const Ray &normAndPoint, double height, double width, double caseSize);
	~Draughtboard();

	Set<double> intersect(const Ray& r) const;
	Vector3 normal(const Vector3& pt) const;
	Color get_color(const Vector3 &pt);
};
//*/
#endif /* DRAUGHTBOARD_H_ */
