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
/*
using namespace std;

int main(int argc, char **argv) {
	cerr << "test huhu" << endl;

	Vector3 obs(0.0, 0.0, 0.0);
	Vector3 aimedPoint(0.0, 10.0, 0.0);
	double distScreen = 2.0;
	int w = 500;
	int h = 500;
	Screen s = Screen(obs, aimedPoint, distScreen, double(w), double(h));
	Vector3 r;
	cerr << "avant construction: w" << w << ";h" << h << endl;
	Image img(w, h, Color(0.0, 0.0, 0.0));
	cerr << "apres construction: u" << w << ";h" << h << endl;
	cerr << "apres construction2: u" << w << ";h" << h << endl;

	/*
	 * CODE GYGLIM
	 * TEST: Intersect sample sphere
	 *//*
	Ray ray = Ray(Vector3(0,0,0),Vector3(1,0,10));
	Sphere sphere = Sphere(Vector3(0,0,250),20, Color(255,0,0));
	Set<Vector3> ip = sphere.intersect(ray);
	cout << "Intersectionpoint: 1";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout <<  ip[0][2];

	cout << "Intersectionpoint: 2";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout <<  ip[0][2];

	// TODO: lancer le rayon
	cerr << "a" << endl;
	for ( int y = 0; y < h; ++y )
	{
		for ( int x = 0; x < w; ++x )
		{
			Ray r2 = Ray(obs,Vector3(x-w/2,y-h/2,400) - obs);
			//img.setPixel ( x, y, Color(0.5,0.5,0.5) );
			Set<Vector3> intersections = sphere.intersect(r2);
			if (!intersections.empty()) {
				img.setPixel ( x, y, sphere.color);
			} else {
				img.setPixel ( x, y, Color(0,0,0));
			}
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
	/*
	 * END CODE GYGLIM
	 */

//*/
/*
	//Valentin
	Sphere sphere = Sphere(Vector3(250, 250, -1000), 150, Color(0.650, 0.152, 0));
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			Ray ray = Ray(Vector3(-1, 0, 0), Vector3(x, y, 0));
			Set<Vector3> ip = sphere.intersect(ray);
			if (sphere.intersect(ray, -1, 1))
				for (int k = 0; k < ip.length(); k++)
					cout << ip.get(k);
				 cout << endl;
				img.setPixel(x, y, sphere.color);
		}
	}
	ofstream myfile;
	myfile.open("sphere.ppm");
	img.writePPM(myfile);
	myfile.close();
//*//*
	return 0;
} // main ()
//*/
