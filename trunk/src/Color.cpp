#include "Color.h"
#include <stdint.h>

Color::Color(double r/*= 0.0*/, double g/*= 0.0*/, double b/*= 0.0*/) {
	val[0] = r;
	val[1] = g;
	val[2] = b;
}

Color::Color(const Color &c) {
	*this = c;
}

Color::~Color() {
}

double Color::getR() const {
	return val[0];
}

double Color::getG() const {
	return val[1];
}

double Color::getB() const {
	return val[2];
}

void Color::setR(double r) {
	val[0] = r;
}

void Color::setG(double g) {
	val[1] = g;
}

void Color::setB(double b) {
	val[2] = b;
}

double& Color::operator[](unsigned i) {
	return val[i];
}

double Color::operator[](unsigned i) const {
	return val[i];
}

bool operator==(const Color &c1, const Color &c2) {
	return c1[0] == c2[0] && c1[1] == c2[1] && c1[2] == c2[2];
}

bool operator!=(const Color &c1, const Color &c2) {
	return !(c1 == c2);
}

const Color& Color::operator+() const {
	return *this;
}

Color Color::operator-() const {
	return Color(-val[0], -val[1], -val[2]);
}

Color& Color::operator=(const Color &c) {
	val[0] = c[0];
	val[1] = c[1];
	val[2] = c[2];
	return *this;
}

Color operator+(const Color &c1, const Color &c2) {
	return Color(c1[0] + c2[0], c1[1] + c2[1], c1[2] + c2[2]);
}

Color operator*(const Color &c1, const Color &c2) {
	return Color(c1[0] * c2[0], c1[1] * c2[1], c1[2] * c2[2]);
}

Color operator/(const Color &c1, const Color &c2) {
	return Color(c1[0] / c2[0], c1[1] / c2[1], c1[2] / c2[2]);
}

Color operator*(const double k, const Color &c) {
	return Color(c[0] * k, c[1] * k, c[2] * k);
}

Color operator*(const Color &c, const double k) {
	return Color(c[0] * k, c[1] * k, c[2] * k);
}

Color operator/(const Color &c, const double k) {
	return Color(c[0] / k, c[1] / k, c[2] / k);
}

Color& Color::operator+=(const Color &c) {
	return *this = *this + c;
}

Color& Color::operator*=(const Color &c) {
	return *this = *this * c;
}

Color& Color::operator/=(const Color &c) {
	return *this = *this / c;
}

Color& Color::operator*=(const double k) {
	return *this = *this * k;
}

Color& Color::operator/=(const double k) {
	return *this = *this / k;
}

void Color::clamp() {
	if (val[0] < 0)
		val[0] = 0;
	if (val[1] < 0)
		val[1] = 0;
	if (val[2] < 0)
		val[2] = 0;

	if (val[0] > 1)
		val[0] = 1;
	if (val[1] > 1)
		val[1] = 1;
	if (val[2] > 1)
		val[2] = 1;
}

std::ostream& operator<<(std::ostream &os, const Color &c) {
	os << "rgb(" << c[0] << ", " << c[1] << ", " << c[2] << ")";
	return os;
}

/*
 Improvement:

 uint32_t Color::getRGB () const
 {
 uint32_t res = 0;
 res |= (int(val[0]*255) & 0xff) << 16;
 res |= (int(val[1]*255) & 0xff) << 8;
 res |= (int(val[2]*255) & 0xff);
 return res;
 }
 */
