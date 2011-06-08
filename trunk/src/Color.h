/*
 * Couleur.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin, Michelet Valentin
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>


using namespace std;
/*
 * set(CMAKE_CXX_FLAGS "-Wall -g")
 *
 * add_executable(nom_executable
 * 					fichier1
 * 					fichier2)
 */
class Color {
public:
	double val[3];

	Color(double r = 0.0, double g = 0.0, double b = 0.0);
	Color(const Color &c);
	virtual ~Color();

	double get_r() const;
	double get_g() const;
	double get_b() const;

	void set_r(double r);
	void set_g(double g);
	void set_b(double b);

	double& operator[] (unsigned i);
	double operator[] (unsigned i) const;

	friend bool operator==(const Color &c1, const Color &c2);
	friend bool operator!=(const Color &c1, const Color &c2);

	const Color& operator+() const;
	Color operator-() const;

	Color& operator=(const Color &c);

	friend Color operator+(const Color &c1, const Color &c2);
	friend Color operator*(const Color &c1, const Color &c2);
	friend Color operator/(const Color &c1, const Color &c2);
	friend Color operator*(const double k, const Color &c);
	friend Color operator*(const Color &c, const double k);
	friend Color operator/(const Color &c, const double k);

	Color& operator+=(const Color &c);
	Color& operator*=(const Color &c);
	Color& operator/=(const Color &c);
	Color& operator*=(const double k);
	Color& operator/=(const double k);

	void clamp();
	friend ostream& operator<<(ostream &os, const Color &c);

};

#endif /* COLOR_H_ */
