#include "Quadrics.h"

Quadrics::Quadrics(const Color &color, const Material &material, double a,
		double b, double c, double d, double e, double f, double g, double h,
		double i, double j) :
	_a(a), _b(b), _c(c), _d(d), _e(e), _f(f), _g(g), _h(h), _i(i), _j(j) {
	this->_color = color;
	this->_material = material;
}

Quadrics::~Quadrics() {
}

Vector3 Quadrics::normal(const Vector3& pt) const {
	double x0 = pt[0];
	double y0 = pt[1];
	double z0 = pt[2];
	return Vector3(2 * x0 + 2 * _e * z0 + 2 * _f * y0 + _g,
			2 * y0 + 2 * _d * z0 + 2 * _f * x0 + _h,
			2 * z0 + 2 * _d * y0 + 2 * _e * x0 + _i);
}

Set<double> Quadrics::intersect(const Ray& r) const {
	Set<double> res;

	double ox = r[0][0];
	double oy = r[0][1];
	double oz = r[0][2];
	double dx = r[1][0];
	double dy = r[1][1];
	double dz = r[1][2];

	double alpha = _a * dx * dx + _b * dy * dy + _c * dz * dz + 2 * _d * dy
			* dz + 2 * _e * dx * dz + 2 * _f * dx * dy;
	double beta = 2 * _a * ox * dx + 2 * _b * oy * dy + 2 * _c * oz * dz + 2
			* _d * (oy * dz + oz * dy) + 2 * _e * (ox * dz + oz * dx) + 2 * _f
			* (ox * dy + oy * dx) + _g * dx + _h * dy + _i * dz;
	double gamma = _a * ox * ox + _b * oy * oy + _c * oz * oz + 2 * _d * oy
			* oz + 2 * _e * ox * oz + 2 * _f * oy * oz + _g * ox + _h * oy + _i
			* oz + _j;

	double delta = beta * beta - 4 * alpha * gamma;

	delta = sqrt(delta);
	if (delta == 0) {
		res.add(-beta / (2 * alpha));
	} else if (delta > 0) {
		res.add((-beta - delta) / (2 * alpha));
		res.add((-beta + delta) / (2 * alpha));
	}

	return res;
}
