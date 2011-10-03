#ifndef SPHERE_H_
#define SPHERE_H_

#include "Shape.h"
#include "Material.h"
#include "Vector3.h"

class Sphere : public Shape {
public:
	Vector3 _center;
	double _radius;

	Sphere (const Color &color = 0, const Material &material = 0, const Vector3 &center = 0, double radius = 0);
	virtual ~Sphere();

	void setMaterial(const Material &material);

	virtual Set<double> intersect (const Ray& ray) const;
	virtual Vector3 normal (const Vector3& pointIntersection) const;
};

#endif /* SPHERE_H_ */
