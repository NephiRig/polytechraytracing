#include "ShapeIntersection.h"

ShapeIntersection::ShapeIntersection(Shape *shape1, Shape *shape2) {
	_shape1 = shape1;
	_shape2 = shape2;
}

ShapeIntersection::~ShapeIntersection() {
}

Vector3 ShapeIntersection::normal(const Vector3& ptIntersect) const {
	return _shape1->normal(ptIntersect);
}

Set<double> ShapeIntersection::ensIntersect(const Ray& rayon) const {
	Set<double> s = Set<double>();
	Set<double> s1 = _shape1->ensIntersect(rayon);
	Set<double> s2 = _shape2->ensIntersect(rayon);

	if (s1.empty() || s2.empty()) {
		return s;
	} else if (s1[0] < s2[0]) {
		return s2;
	} else {
		return s1;
	}
}

Color ShapeIntersection::getColor(const Vector3& ptIntersect) {
	if (_shape2->belongsTo(ptIntersect)) {
		_material = _shape2->_material;
		return _shape2->_color;
	} else if (_shape1->belongsTo(ptIntersect)) {
		_material = _shape1->_material;
		return _shape1->_color;
	} else {
		return Color();
	}

}

bool ShapeIntersection::belongsTo(const Vector3& ptIntersect) const {
	return _shape1->belongsTo(ptIntersect) || _shape2->belongsTo(ptIntersect);
}
