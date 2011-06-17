#ifndef SHAPE_H_
#define SHAPE_H_

#include "Vector3.h"
#include "Color.h"
#include "Ray.h"
#include "Set.h"
#include "Material.h"

class Shape {
public:
	Color _color;
	Material _material;

	Shape();
	virtual ~Shape();

	virtual Vector3 normal(const Vector3& pt) const=0;
	virtual Set<double> intersect(const Ray& r) const=0;
	virtual Color getColor(const Vector3& pt);
};

#endif /* SHAPE_H_ */
