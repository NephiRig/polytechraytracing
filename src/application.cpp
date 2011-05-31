/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>

using namespace std;


int main ( int argc, char **argv )
{
	cout << "test huhu" << endl;

	Vector3 obs ( 0.0, 0.0, 0.0 );
	Vector3 aimedPoint ( 0.0, 10.0, 0.0 );
	double distScreen = 2.0;
	double Rx = 400.0;
	double Ry = 300.0;
	Screen s = Screen ( obs, aimedPoint, distScreen, Rx, Ry );
	// TODO: lancer le rayon

	return 0;
} // main ()

