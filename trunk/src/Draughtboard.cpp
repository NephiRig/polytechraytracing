#include "Draughtboard.h"
#include <cmath> //floor(), fabs()

Draughtboard::Draughtboard(const Color &color, const Material &material, const Color &colorD, const Ray &normAndPoint, double height, double width, double caseSize) :
	Rectangle(color, material, normAndPoint, height, width), _colorD(colorD), _caseSize(caseSize) {
}

Draughtboard::~Draughtboard() {
}

Color Draughtboard::getColor(const Vector3 &ptIntersect) {
	if ((int) floor( fabs((ptIntersect / _caseSize)[0])+.5 ) % 2 == (int) floor( fabs((ptIntersect / _caseSize)[2])+.5 ) % 2) {
		return _color;
	} else {
		return _colorD;
	}
}
