#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Shape.h"

class ShapeIntersection : public Shape {
public:
	Shape *_shape1;
	Shape *_shape2;

	ShapeIntersection(Shape *shape1, Shape *shape2);
	virtual ~ShapeIntersection();

	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual Color getColor(const Vector3 &ptIntersect);
	virtual bool belongsTo(const Vector3& ptIntersect) const;
};

#endif /* INTERSECTION_H_ */
