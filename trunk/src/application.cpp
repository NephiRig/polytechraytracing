/*
 * application.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include <iostream>
#include <fstream> // ofstream

#include "Vector3.h"
#include "Screen.h"
#include "Sphere.h"
#include "Ray.h"
#include "Image.h"


using namespace std;


int main ( int argc, char **argv )
{
	cerr << "test huhu" << endl;

	Vector3 obs ( 0.0, 0.0, 0.0 );
	Vector3 aimedPoint ( 0.0, 10.0, 0.0 );
	double distScreen = 2.0;
	int w = 400;
	int h = 300;
	Screen s = Screen ( obs, aimedPoint, distScreen, double(w), double(h) );
	Vector3 r;
	cerr << "avant construction: w" << w << ";h" << h << endl;
	Image img ( w, h, Color(0.0,0.0,0.0) );
	cerr << "apres construction: u" << w << ";h" << h << endl;
	cerr << "apres construction2: u" << w << ";h" << h << endl;

	//TEST: Intersect sample sphere:
	/*Ray ray = Ray(Vector3(0,0,0),Vector3(1,0,0));
	Sphere sphere = Sphere(Vector3(20,0,0),10);
	Set<Vector3> ip = sphere.intersect(ray);
	cout << "Intersectionpoint: 1";
	cout << "x=";
	cout << ip.get(0)[0];
	cout << " y=";
	cout << ip.get(0)[1];
	cout << " z=";
	cout <<  ip.get(0)[2];

	cout << "Intersectionpoint: 2";
	cout << "x=";
	cout << ip.get(1)[0];
	cout << " y=";
	cout << ip.get(1)[1];
	cout << " z=";
	cout <<  ip.get(1)[2];
	 */
	// TODO: lancer le rayon
	cerr << "a" << endl;
	for ( int y = 0; y < h; ++y )
	{
		for ( int x = 0; x < w; ++x )
		{
			//r = s.getPixel ( x, y ) - obs;
			//img.setPixel ( x, y, Color(0.5,0.5,0.5) );
			img.setPixel ( x, y, Color(x * 1.0 / w, y * 1.0 / h, 0.5) );
		}
	}
	cerr << "b" << endl;
	ofstream myfile;
	myfile.open ("img.ppm");
	cerr << "on tente le writePPM" << endl;
	img.writePPM ( myfile );
	cerr << "fin du writePPM" << endl;
	//img.writePPM ( cerr );
	cerr << endl;
	myfile.close ();

	return 0;
} // main ()

