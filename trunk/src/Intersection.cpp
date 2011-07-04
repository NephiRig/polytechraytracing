#include "Intersection.h"
#include <cmath>

Intersection::Intersection(Shape *shape, const Ray &rayon) :
	_rayon(rayon) {
	_shape = shape;
	_intersections = _shape->ensIntersect(rayon);
	if (_intersections.length() > 0) {
		if (_intersections.length() > 1) {
			quickSort(_intersections, 0, _intersections.length() - 1);
		}
		double firstT = _intersections[0];
		_normal = _shape->normal(rayon.getPoint(firstT));
		_color = _shape->getColor(rayon.getPoint(firstT));
	} else {
		_normal = Vector3();
		_color = Color();
	}
}

Intersection::~Intersection() {
}
/*
double minTAux(Set<double> array, int indexStart, double minValue) {
	if (indexStart == array.length()) {
		return minValue;
	} else if (minValue > array[indexStart]) {
		minValue = array[indexStart];
		return minTAux(array, ++indexStart, minValue);
	} else {
		return minTAux(array, ++indexStart, minValue);
	}
}

double minT(Set<double> array) {
	if (array.length() == 0) {
		return -1;
	} else if (array.length() == 1) {
		return array[0];
	} else {
		return minTAux(array, 0, array[0]);
	}
}
//*/
//*
void Intersection::quickSort(Set<double> array, int left, int right) {
	if (right > left) {
		int pivotIndex = floor((right + left) / 2);
		int pivotNewIndex = partition(array, left, right, pivotIndex);
		quickSort(array, left, pivotNewIndex - 1);
		quickSort(array, pivotNewIndex + 1, right);
	}
}

int Intersection::partition(Set<double> array, int left, int right, int pivotIndex) {
	double pivotValue = array[pivotIndex];
	double tmp = pivotValue;
	array[pivotIndex] = array[right];
	array[right] = tmp;
	int storeIndex = left;
	for (int i = left; i < right; i++) {
		if (array[i] < pivotValue) {
			tmp = array[i];
			array[i] = array[storeIndex];
			array[storeIndex] = tmp;
			storeIndex++;
		}
	}
	tmp = array[storeIndex];
	array[storeIndex] = array[right];
	array[right] = tmp;
	return storeIndex;
}
//*/
