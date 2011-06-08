/*
 * RayTracer.cpp
 *
 *  Created on: 08.06.2011
 *      Author: nb-gyglim
 */

#include "RayTracer.h"

RayTracer::RayTracer() {
	// TODO Auto-generated constructor stub

}

RayTracer::~RayTracer() {
	// TODO Auto-generated destructor stub
}


Image* RayTracer::raytrace() {
	Vector3 obs(0, 0, 0.0);
	Vector3 aimedPoint(0, 0, 250.0);
	double distScreen = 150.0;
	int w = 500;
	int h = 500;
	Screen s = Screen(obs, aimedPoint, distScreen, double(w), double(h));
	Sphere sphere = Sphere(Vector3(0, 0, 200), 100, Color(1, 0, 0));
	Sphere sphere2 = Sphere(Vector3(70, 70, 80), 2, Color(1, 1, 0.5));
	Rectangle rect = Rectangle(100, Vector3(1, 0, 0), Color(0, 0, 1));
	Set<Shape> shapes = Set<Shape> (3);
	shapes.add(sphere);
	shapes.add(sphere2);
	//shapes.add(rect);
	LightSource source = LightSource(1, Vector3(70, 70, 80), Color(1, 1, 0.5));
	Vector3 r;
	cerr << "avant construction: w" << w << ";h" << h << endl;
	Image* img = new Image(w, h, Color(0.0, 0.0, 0.0));
	cerr << "apres construction: u" << w << ";h" << h << endl;
	cerr << "apres construction2: u" << w << ";h" << h << endl;

	/*
	 * CODE GYGLIM
	 * TEST: Intersect sample sphere
	 */
	Ray ray = Ray(Vector3(0, 0, 0), Vector3(1, 0, 10));
	Set<Vector3> ip = sphere.intersect(ray);
	cout << "Intersectionpoint: 1";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout << ip[0][2];

	cout << "Intersectionpoint: 2";
	cout << "x=";
	cout << ip[0][0];
	cout << " y=";
	cout << ip[0][1];
	cout << " z=";
	cout << ip[0][2];

	// TODO: lancer le rayon
	PhongModel lm = PhongModel();
	cerr << "a" << endl;
	for (int y = 0; y < h; ++y) {
		for (int x = 0; x < w; ++x) {
			Ray r2 = Ray(obs, s.getPixel(x, y) - obs);
			for (int i = 0; i < shapes.length(); i++) {
				Shape s = shapes.get(i);
				Set<Vector3> intersections = s.intersect(r2);
				if (!intersections.empty()) {
					Vector3 n = s.normal(intersections[0]);
					Ray normal = Ray(intersections[0], n);

					Ray reflected = Ray(
							intersections[0],
							2 * n * dot_product(n, r2.get_direction())
									- r2.get_direction());
					Color c = Color(s.color);
					double ambient = lm.getAmbient();
					double diffuse = lm.getDiffuse(normal, source);
					double specular = lm.getSpecular(reflected, source);
					img->setPixel(x, y,
							ambient * c + diffuse * c + specular * source.color);
				} else {
					//img.setPixel(x, y, Color(0, 0, 0));
				}
/*
				Set<Vector3> intersections2 = sphere2.intersect(r2);
				if (!intersections2.empty()) {
					img.setPixel(x, y, sphere2.color);
				}*/
			}
		}
	}
	/*cerr << "b" << endl;
	ofstream myfile;
	myfile.open("img8.ppm");
	cerr << "on tente le writePPM" << endl;
	img.writePPM(myfile);
	cerr << "fin du writePPM" << endl;
	//img.writePPM ( cerr );
	cerr << endl;
	myfile.close();*/
	return img;
}
