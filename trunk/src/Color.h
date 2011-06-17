#ifndef COLOR_H_
#define COLOR_H_

#include <iostream>

class Color {
public:
	double val[3];

	Color(double r = 0.0, double g = 0.0, double b = 0.0);
	Color(const Color &c);
	virtual ~Color();

	double getR() const;
	double getG() const;
	double getB() const;

	void setR(double r);
	void setG(double g);
	void setB(double b);

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
	friend std::ostream& operator<<(std::ostream &os, const Color &c);

	//Improvement:
	//uint32_t getRGB () const;

};

#endif /* COLOR_H_ */
