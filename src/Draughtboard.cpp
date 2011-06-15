/*
 * Draughtboard.cpp
 *
 *  Created on: 8 juin 2011
 *      Author: michelet
 */

#include "Draughtboard.h"
#include <cmath> //floor(), fabs()

Draughtboard::Draughtboard(const Color &color, const Material &material, const Color &colorD, const Ray &normAndPoint, double height, double width, double caseSize) :
	Rectangle(color, material, normAndPoint, height, width), _colorD(colorD), _caseSize(caseSize) {
}

Draughtboard::~Draughtboard() {
	// TODO Auto-generated destructor stub
}

Color Draughtboard::getColor(const Vector3 &pt) {
	if ((int) floor( fabs((pt / _caseSize)[0])+.5 ) % 2 == (int) floor( fabs((pt / _caseSize)[2])+.5 ) % 2) {
		return Shape::_color;
	} else {
		return _colorD;
	}
}
