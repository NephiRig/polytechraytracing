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
	/*
	 * FIXME gyglim change formula to have (0,0) at the upper left
	 */
	Vector3 OA = aimedPoint - observer;
	Vector3 a = OA.normalized ();
	a *= distScreen;
    std::cout << "\n a: x=" << a[0] << ";y=" << a[1] << ";z=" << a[2] << "\n";
	w = Vector3(1,a.coords[0]/a.coords[2]);
	w.normalize();
    std::cout << "w: " << w;

	h = cross_product(a,w);
	h.normalize();
    std::cout << "h: " << h;

	ptI= a - w*Rx/2 - h*Ry/2;
    std::cout << "ptI: x=" << ptI[0] << ";y=" << ptI[1] << ";z=" << ptI[2] << "\n";
}

Screen::~Screen()
{}


Vector3 Screen::getPixel ( int x, int y )
{
	Vector3 res;
	res = ptI + x*w + y*h;
	/*if ((x ==Rx-1 || x==0) && (y==Ry-1 || y==0)) {
		cout << "\n x=" << res[0] << ";y=" << res[1] << ";z=" << res[2];
	}*/
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
