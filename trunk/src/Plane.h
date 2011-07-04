#ifndef PLANE_H_
#define PLANE_H_

#include "Shape.h"

class Plane : public Shape {
public:
	Ray _normAndPoint;
	double _d;

	Plane(const Color &color, const Material &material, const Ray &normAndPoint);
	virtual ~Plane();

	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual bool belongsTo(const Vector3 &ptIntersect) const;
	/*
	virtual Intersection getIntersectParams(const Ray &rayon) const;
	//*/
};

#endif /* PLANE_H_ */
