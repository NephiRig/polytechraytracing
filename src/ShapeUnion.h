#ifndef SHAPEUNION_H_
#define SHAPEUNION_H_

#include "Shape.h"

class ShapeUnion : public Shape {
public:
	Shape *_shape1;
	Shape *_shape2;

	ShapeUnion(Shape *shape1, Shape *shape2);
	virtual ~ShapeUnion();

	virtual Vector3 normal(const Vector3 &ptIntersect) const;
	virtual Set<double> ensIntersect(const Ray &rayon) const;
	virtual Color getColor(const Vector3 &ptIntersect);
	virtual bool belongsTo(const Vector3 &ptIntersect) const;
};

#endif /* SHAPEUNION_H_ */
