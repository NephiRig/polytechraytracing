#include "ShapeUnion.h"

ShapeUnion::ShapeUnion(Shape *shape1, Shape *shape2) {
	_shape1 = shape1;
	_shape2 = shape2;
}

ShapeUnion::~ShapeUnion() {
}

Vector3 ShapeUnion::normal(const Vector3 &ptIntersect) const {
	if (_shape2->belongsTo(ptIntersect)) {
		return _shape2->normal(ptIntersect);
	} else if (_shape1->belongsTo(ptIntersect)) {
		return _shape1->normal(ptIntersect);
	} else {
		return Vector3();
	}
}

Set<double> ShapeUnion::ensIntersect(const Ray &rayon) const {
	Set<double> s = Set<double>();
	Set<double> s1 = _shape1->ensIntersect(rayon);
	Set<double> s2 = _shape2->ensIntersect(rayon);

	for (int i = 0; i < s1.length(); i++) {
		s.add(s1[i]);
	}
	for (int i = 0; i < s2.length(); i++) {
		s.add(s2[i]);
	}

	return s;
}

Color ShapeUnion::getColor(const Vector3 &ptIntersect) {
	if (_shape2->belongsTo(ptIntersect)) {
		_material = _shape2->_material;
		return _shape2->getColor(ptIntersect);
	} else if (_shape1->belongsTo(ptIntersect)) {
		_material = _shape1->_material;
		return _shape1->getColor(ptIntersect);
	} else {
		return Color();
	}
}

bool ShapeUnion::belongsTo(const Vector3 &ptIntersect) const {
	return _shape1->belongsTo(ptIntersect) || _shape2->belongsTo(ptIntersect);
}
