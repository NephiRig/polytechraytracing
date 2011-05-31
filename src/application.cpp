/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>

#include "Vector3.h"
#include "Screen.h"

using namespace std;


int main ( int argc, char **argv )
{
	cout << "test huhu" << endl;

	Vector3 obs ( 0.0, 0.0, 0.0 );
	Vector3 aimedPoint ( 0.0, 10.0, 0.0 );
	double distScreen = 2.0;
	int w = 400;
	int h = 300;
	Screen s = Screen ( obs, aimedPoint, distScreen, (double)w, (double)h );
	Vector3 r;
	// TODO: lancer le rayon
	for ( int y = 0; y < h; ++y )
	{
		for ( int x = 0; x < w; ++x )
		{
			r = s.getPixel ( x, y ) - obs;

		}
	}

	return 0;
} // main ()

