#ifndef LIGHTSOURCE_H_
#define LIGHTSOURCE_H_

#include "Vector3.h"
#include "Color.h"

class LightSource {
public:
	LightSource(double intens, const Vector3 &pos, const Color &c) ;
	virtual ~LightSource();

	double intensity;
	Color color;
	Vector3 position;
};

#endif /* LIGHTSOURCE_H_ */
