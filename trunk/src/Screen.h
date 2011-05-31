/*
 * Screen.h
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "Vector3.h"
#include "Vector2.h"

class Screen {
public:
	Vector3 observer;
	Vector3 aimedPoint;
	double distScreen;
	double Rx;
	double Ry;
	Vector3 ptI;

	Screen ( Vector3 _observer, Vector3 _aimedPoint, double _distScreen, double _Rx, double _Ry );
	virtual ~Screen();

	Vector3 getPixel ( int x, int y );
	Vector3 getPixel ( Vector2 pt );
};

#endif /* SCREEN_H_ */
