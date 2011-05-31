/*
 * Couleur.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef COULEUR_H_
#define COULEUR_H_

class Couleur {
public:
	Couleur ( double r = 0.0, double v = 0.0, double b = 0.0 );
	virtual ~Couleur();
	double val[];
};

#endif /* COULEUR_H_ */
