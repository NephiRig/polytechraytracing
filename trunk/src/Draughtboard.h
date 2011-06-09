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
class Draughtboard : public Shape {
public:
	Color color_d;
	Vector3 o;
	Vector3 x;
	Vector3 y;
	double length;

	Draughtboard() {};
	Draughtboard(const Color &_color, const Color &_color_d, const Vector3 &_o, const Vector3 &_x, const Vector3 &_y, double length);
	virtual ~Draughtboard();

	Color get_color(const Vector3 &pt);
};
//*/
#endif /* DRAUGHTBOARD_H_ */
