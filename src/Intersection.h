#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include "Color.h"
#include "Set.h"
#include "Shape.h"
#include "Vector3.h"

class Intersection {
public:
	Set<double> _intersections;
	Vector3 _normal;
	Color _color;
	Shape *_shape;
	Ray _rayon;

	Intersection(Shape *shape, const Ray &rayon);
	virtual ~Intersection();

	//*
	void quickSort(Set<double> array, int left, int right);
	int partition(Set<double> array, int left, int right, int pivotIndex);
	//*/
	/*
	friend double minT(Set<double> array);
	friend double minTAux(Set<double> array, int indexStart, double minValue);
	//*/
};

#endif /* INTERSECTION_H_ */
