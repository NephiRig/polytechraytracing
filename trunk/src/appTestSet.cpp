#include <iostream>

#include "Set.h"
#include "Shape.h"
#include "Sphere.h"

using namespace std;

int main ()
{
	cerr << "test de Set" << endl;
	{
	cerr << "- set de double" << endl;
	Set<double> s = Set<double> ();
	cerr << "créé" << endl;
	s.add(10.0);
	s.add(15.0);
	cerr << "ajoutés" << endl;
	cerr << "el 0: " << s.get(0) << endl;
	cerr << "el 1: " << s.get(1) << endl;
	}
	{
	cerr << "- set de Shape*" << endl;
	Set<Shape*> a = Set<Shape*> ();
	cerr << "créé" << endl;
	Sphere* b = new Sphere (Vector3(0.0,0.0,0.0), 5.0, Color(1.0,0.0,0.0));
	Sphere* c = new Sphere (Vector3(1.0,0.0,0.0), 5.0, Color(0.0,0.0,1.0));
	a.add ( (Shape*)b );
	a.add ( (Shape*)c );
	cerr << "ajoutés" << endl;
	cerr << "el 0: " << a.get(0) << endl;
	cerr << "el 1: " << a.get(1) << endl;
	delete b;
	delete c;
	}

	cerr << "fin du test de Set" << endl;

	return 0;
}
