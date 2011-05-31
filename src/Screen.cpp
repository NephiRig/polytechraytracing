/*
 * Screen.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Screen.h"


Screen::Screen ( Vector3 _observer, Vector3 _aimedPoint, double _distScreen, double _Rx, double _Ry )
	: observer(_observer), aimedPoint(_aimedPoint), distScreen(_distScreen), Rx(_Rx), Ry(_Ry)
{
	Vector3 OA = aimedPoint - observer;
	Vector3 a = OA.normalized ();
	a *= distScreen;
	ptI[0] = a[0] - Rx / 2.0;
	ptI[1] = a[1];
	ptI[2] = a[2] + Ry / 2.0;
}

Screen::~Screen()
{}


Vector3 Screen::getPixel ( int x, int y )
{
	Vector3 res;
	res[0] = ptI[0] + x * 1.0 / Rx;
	res[1] = ptI[1];
	res[2] = ptI[2] + y * 1.0 / Ry;
	return res;
}

Vector3 Screen::getPixel ( Vector2 pt )
{
	Vector3 res;
	res[0] = ptI[0] + pt[0] * 1.0 / Rx;
	res[1] = ptI[1];
	res[2] = ptI[2] + pt[1] * 1.0 / Ry;
	return res;
}
