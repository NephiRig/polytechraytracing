/*
 * Couleur.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Color.h"

Color::Color ( double r/*= 0.0*/, double v/*= 0.0*/, double b/*= 0.0*/ )
{
	val[0] = r;
	val[1] = v;
	val[2] = b;
}

Color::~Color() {
	// TODO Auto-generated destructor stub
}
