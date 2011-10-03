#ifndef QUADRICS_H_
#define QUADRICS_H_

#include "Shape.h"
#include <cmath>

class Quadrics: public Shape {
public:
	double _a, _b, _c, _d, _e, _f, _g, _h, _i, _j;

	Quadrics(const Color &color, const Material &material, double a, double b, double c, double d, double e, double f,
			double g, double h, double i, double j);
	virtual ~Quadrics();

	virtual Vector3 normal(const Vector3& pt) const;
	virtual Set<double> intersect(const Ray& r) const;

};

#endif /* QUADRICS_H_ */
