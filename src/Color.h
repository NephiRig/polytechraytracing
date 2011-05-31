/*
 * Couleur.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef COLOR_H_
#define COLOR_H_

class Color {
public:
	Color ( double r = 0.0, double v = 0.0, double b = 0.0 );
	virtual ~Color();
	double val[];
};

#endif /* COLOR_H_ */
