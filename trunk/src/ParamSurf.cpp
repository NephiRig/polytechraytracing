/*
 * ParamSurf.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: Marion & Sandra
 */

#include "ParamSurf.h"


extern "C"{
void zggev_(char *jobvl, char *jobvr, int *n, double *a, int *lda, double *b, int *ldb, double *alpha,double *beta, double *vl, int *ldvl, double *vr, int *ldvr,double *work, int *lwork, double *rwork, int *info);
}


ParamSurf::ParamSurf(const Color &_color,mat M0, mat M1, mat M2, mat M3) : 
	 M0(M0), M1(M1), M2(M2), M3(M3) {
	this->color = _color;
	material=Material(0.1,0.4,0.5,20); //FIXME Take into constructor
}

ParamSurf::~ParamSurf() {
}

/*
 *	Calculate the pencil of a parametric surface
 */
Set<mat> ParamSurf::make_pencil(const Ray& r) const {


	Set<mat> pencil = Set<mat> (2);

	Vector3 originRay = r.get_origin();
	Vector3 directionRay = r.get_direction();

	double x0 = originRay.get_x();
	double y0 = originRay.get_y();
	double z0 = originRay.get_z();

	double xd = directionRay.get_x();
	double yd = directionRay.get_y();
	double zd = directionRay.get_z();

	
	mat A = xd*M1+yd*M2+zd*M3;
	mat B = x0*M1+y0*M2+z0*M3+M0;
/*
	double [][] A;
	double [][] B;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			A[i][j] = M1[i][j]*xd+M2[i][j]*yd+M3[i][j]*zd;
			B[i][j] =  M1[i][j]*x0+M2[i][j]*y0+M3[i][j]*z0+M0[i][j];
		}
	}
*/
	pencil.add(A);
	pencil.add(B);

	return pencil;
}

/*
 *	Calculate the intersections of a ray with a parametric surface
 */
Set<double> ParamSurf::intersect(const Ray& r) const {

	Set<mat> pencil = make_pencil(r);

	mat A = pencil.get(1);
	mat B = pencil.get(2);

	cout << "A = " << A << endl;
	cout << "B = " << B << endl;

	vec lambda;
	mat evecs;
	char jobvl = 'N', jobvr = 'V';
	int n, lda, ldb, ldvl, ldvr, lwork, info;
	n=lda=A.rows();
	ldb = B.rows();
	ldvl = 1;
	ldvr = n;
	lwork = std::max(1,  n*n+64); // This may be choosen better! ???

	vec work(lwork);
	vec rwork(8*n); // This may be choosen better
	vec alpha(n), beta(n);
	mat vl(1,1), vr(n, n);
	zggev_(&jobvl, &jobvr, &n, A._data(), &lda,
        B._data(), &ldb, alpha._data(),  beta._data(), vl._data(),
        &ldvl, vr._data(), &ldvr, work._data(), &lwork,
        rwork._data(), &info);
	lambda=elem_div(alpha,beta);
	cout<<endl;
	cout<< "eig(A,B)= \n";

	Set<double> gev = Set<double>(6);
	for(int i=0;sizeof(lambda);i++){
		gev.add(lambda(i));
	}


	cout << "lambda = "<< lambda <<endl;
	return gev;
}

Vector3 ParamSurf::normal(const Vector3& pt_intersection) const {
	return Vector3(1, 0, 0);
}


int main(){
	/*mat M0 = "-1,0,0,0,0,-2; 0,-2,0,0,0,0; 0,0,0,0,-2,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,-8,-8";
	mat M1 = "-1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,0,-4";
	mat M2 = "0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,-2; 0,0,0,-2,0,0; 0,4,0,0,0,0";
	mat M3 = "0,0,0,0,0,0; 0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,2,0,0; 2,0,0,0,0,0; 0,0,0,0,6,0";
	
	ParamSurf* paramSurf1 = new ParamSurf(Color(0,1,0),M0,M1,M2,M3);
	Vector3 origin= Vector3(2,1,2) const Vector3 &direction
	paramSurf1.intersect(*/
}

