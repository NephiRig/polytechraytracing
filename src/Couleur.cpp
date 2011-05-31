/*
 * Couleur.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Couleur.h"

Couleur::Couleur ( double r/*= 0.0*/, double v/*= 0.0*/, double b/*= 0.0*/ )
{
	val[0] = r /*< 0.0 ? 0.0 : r >= 1.0 ? */;
	val[1] = v;
	val[2] = b;
}

Couleur::~Couleur() {
	// TODO Auto-generated destructor stub
}
