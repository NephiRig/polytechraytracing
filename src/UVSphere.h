#ifndef UVSPHERE_H_
#define UVSPHERE_H_

#include "Sphere.h"
#include "Texture.h"

class UVSphere : public Sphere {
public:
	Texture *_tex;

	UVSphere(const Color &color = 0, const Material &material = 0, const Vector3 &center = 0, float radius = 0, Texture *tex = 0);
	virtual ~UVSphere();

	virtual Color getColor(const Vector3& pointIntersection);
};

#endif /* UVSPHERE_H_ */
