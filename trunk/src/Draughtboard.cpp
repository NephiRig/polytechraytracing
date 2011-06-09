/*
 * Draughtboard.cpp
 *
 *  Created on: 8 juin 2011
 *      Author: michelet
 */

#include "Draughtboard.h"
#include <cmath> //floor()
//*
Draughtboard::Draughtboard(const Color &_color, const Color &_color_d,
		const Vector3 &_o, const Vector3 &_x, const Vector3 &_y, double _length) :
	color_d(_color_d), x(_x), y(_y), o(_o), length(_length) {
	this->color = _color;
}

Draughtboard::~Draughtboard() {
	// TODO Auto-generated destructor stub
}

Color Draughtboard::get_color(const Vector3 &pt) {
	if ((int) floor((pt / length)[0]) % 2 == (int) floor((pt / length)[1]) % 2)
		return color;
	else
		return color_d;
}
//*/
