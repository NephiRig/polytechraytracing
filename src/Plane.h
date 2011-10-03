#ifndef PLANE_H_
#define PLANE_H_

#include "Shape.h"

class Plane : public Shape {
public:
	Ray _normAndPoint;
	double _d;

	Plane(const Color &color, const Material &material, const Ray &normAndPoint);
	virtual ~Plane();

	virtual Set<double> intersect(const Ray& r) const;
	virtual Vector3 normal(const Vector3& pt) const;
};

#endif /* PLANE_H_ */
