#ifndef UVSPHERE_H_
#define UVSPHERE_H_

#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Texture.h"

class UVSphere : public Shape {
public:
	Vector3 _center;
	float _radius;
	Texture *_tex;

	UVSphere(const Color &color, const Material &material, const Vector3 &center, float radius, Texture *tex);
	virtual ~UVSphere();

	Vector3 normal(const Vector3& pt_intersect) const;
	Set<double> intersect(const Ray& r) const;
	virtual Color getColor(const Vector3& pt);
};

#endif /* UVSPHERE_H_ */
