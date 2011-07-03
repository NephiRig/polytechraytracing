#ifndef SHAPE_H_
#define SHAPE_H_

#include "Color.h"
#include "Material.h"
#include "Ray.h"
#include "Set.h"
#include "Vector3.h"

class Shape {
public:
	Color _color;
	Material _material;

	Shape();
	virtual ~Shape();

	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual Color getColor(const Vector3 &ptIntersect) const;
	/*
	virtual Intersection getIntersectParams(const Ray &rayon) const = 0;
	//*/
};

#endif /* SHAPE_H_ */
