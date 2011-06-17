#include "LightSource.h"

LightSource::LightSource(double intens, const Vector3 &pos, const Color &c) {
	intensity = intens;
	position = pos;
	if (c != 0){
		color = c;
	} else {
		color = Color(1,1,1);
	}
}

LightSource::~LightSource() {
}
