/*
 * ParamSurf.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: Marion & Sandra
 */

#include "ParamSurf.h"
#include "math.h"
#include <iostream>

using namespace std;

ParamSurf (const Color &_color, int [][] M0, int [][] M1, int [][] M2, int [][] M3) : 
		color(_color), M0(M0), M1(M1), M2(M2), M3(M3) {
}

ParamSurf::~ParamSurf() {
	// TODO Auto-generated destructor stub
}

/*
 *	Calculate the intersections of a ray with a parametric surface
 */
Set<Vector3> ParamSurf::intersect(const Ray& r) const {

	Set<double[][]> pencil = pencil(r);

	double[][] A = pencil.get(1);
	double[][] B = pencil.get(2);

	//méthode pour trouver les vp généralisées...

	return s; //set containing the generalized eigenvalues
}

/*
 *	Calculate the pencil of a parametric surface
 */
Set<double[][]> ParamSurf::pencil(const Ray& r) const {
/*
	M0 = {{-1,0,0,0,0,-2},{0,-2,0,0,0,0},{0,0,0,0,-2,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{-4,0,0,0,-8,-8}};
	M1 = {{-1,0,1,0,0,-1},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{-4,0,0,0,0,-4}};
	M2 = {{0,0,0,0,0,0},{-1,0,1,0,0,-1},{0,0,0,0,0,0},{0,0,0,0,0,-2},{0,0,0,-2,0,0},{0,4,0,0,0,0}};
	M3 = {{0,0,0,0,0,0},{0,0,0,0,0,0},{-1,0,1,0,0,-1},{0,0,0,2,0,0},{2,0,0,0,0,0},{0,0,0,0,6,0}};
*/

	Set<double[][]> pencil = Set<double[][]> (2);

	Vector3 originRay = r.get_origin();
	Vector3 directionRay = r.get_direction();

	double x0 = originRay.get_x();
	double y0 = originRay.get_y();
	double z0 = originRay.get_z();

	double xd = directionRay.get_x();
	double yd = directionRay.get_y();
	double zd = directionRay.get_z();


	//multiplication matrice scalaire?
	double [][] A =  M1*xd+M2*yd+M3*zd;
	double [][] B =  M1*x0+M2*y0+M3*z0+M0;
	s.add(A);
	s.add(B);

	return pencil;
}

Vector3 ParamSurf::normal(const Vector3& pt) const {
	return Vector3(0, 0, 0);
}
