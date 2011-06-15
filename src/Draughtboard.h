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
#include "Rectangle.h"

class Draughtboard: public Rectangle {
public:
	Color _colorD;
	double _caseSize;

	Draughtboard(const Color &color, const Material &material, const Color &colorD, const Ray &normAndPoint, double height, double width, double caseSize);
	virtual ~Draughtboard();

	virtual Color getColor(const Vector3 &pt);
};
//*/
#endif /* DRAUGHTBOARD_H_ */
