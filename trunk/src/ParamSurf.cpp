/*
 * ParamSurf.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: Marion & Sandra
 */

#include "ParamSurf.h"


extern "C"{
void zggev_(char *jobvl, char *jobvr, int *n, complex<double> *a, int *lda, complex<double> *b, int *ldb, complex<double> *alpha,complex<double> *beta, complex<double> *vl, int *ldvl, complex<double> *vr, int *ldvr,complex<double> *work, int *lwork, double *rwork, int *info);
}


ParamSurf::ParamSurf(const Color &_color, cmat M0, cmat M1, cmat M2, cmat M3) : 
		color(_color), M0(M0), M1(M1), M2(M2), M3(M3) {
}

ParamSurf::~ParamSurf() {
}

/*
 *	Calculate the pencil of a parametric surface
 */
Set<cmat> ParamSurf::make_pencil(const Ray& r) const {


	Set<cmat> pencil = Set<cmat> (2);

	Vector3 originRay = r.get_origin();
	Vector3 directionRay = r.get_direction();

	complex<double> x0 = originRay.get_x();
	complex<double> y0 = originRay.get_y();
	complex<double> z0 = originRay.get_z();

	complex<double> xd = directionRay.get_x();
	complex<double> yd = directionRay.get_y();
	complex<double> zd = directionRay.get_z();

	
	cmat A = xd*M1+yd*M2+zd*M3;
	cmat B = x0*M1+y0*M2+z0*M3+M0;
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
cvec ParamSurf::intersect(const Ray& r) const {

	Set<cmat> pencil = make_pencil(r);

	cmat A = pencil.get(1);
	cmat B = pencil.get(2);

	cout << "A = " << A << endl;
	cout << "B = " << B << endl;

	cvec lambda;
	cmat evecs;
	char jobvl = 'N', jobvr = 'V';
	int n, lda, ldb, ldvl, ldvr, lwork, info;
	n=lda=A.rows();
	ldb = B.rows();
	ldvl = 1;
	ldvr = n;
	lwork = std::max(1,  n*n+64); // This may be choosen better! ???

	cvec work(lwork);
	vec rwork(8*n); // This may be choosen better
	cvec alpha(n), beta(n);
	cmat vl(1,1), vr(n, n);
	zggev_(&jobvl, &jobvr, &n, A._data(), &lda,
        B._data(), &ldb, alpha._data(),  beta._data(), vl._data(),
        &ldvl, vr._data(), &ldvr, work._data(), &lwork,
        rwork._data(), &info);
	lambda=elem_div(alpha,beta);
	cout<<endl;
	cout<< "eig(A,B)= \n";
	cout << "lambda = "<< lambda <<endl;

	return lambda;
}

Vector3 ParamSurf::normal(const Vector3& pt) const {
	return Vector3(0, 0, 0);
}


int main(){

	/*cmat M0 [6][6] = {{-1,0,0,0,0,-2},{0,-2,0,0,0,0},{0,0,0,0,-2,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{-4,0,0,0,-8,-8}};
	cmat M1 [6][6] = {{-1,0,1,0,0,-1},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{0,0,0,0,0,0},{-4,0,0,0,0,-4}};
	cmat M2 [6][6] = {{0,0,0,0,0,0},{-1,0,1,0,0,-1},{0,0,0,0,0,0},{0,0,0,0,0,-2},{0,0,0,-2,0,0},{0,4,0,0,0,0}};
	cmat M3 [6][6] = {{0,0,0,0,0,0},{0,0,0,0,0,0},{-1,0,1,0,0,-1},{0,0,0,2,0,0},{2,0,0,0,0,0},{0,0,0,0,6,0}};*/

	cmat M0 [6][6] = "-1,0,0,0,0,-2; 0,-2,0,0,0,0; 0,0,0,0,-2,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,-8,-8";
	cmat M1 [6][6] = "-1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; 0,0,0,0,0,0; -4,0,0,0,0,-4";
	cmat M2 [6][6] = "0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,0,0,0; 0,0,0,0,0,-2; 0,0,0,-2,0,0; 0,4,0,0,0,0";
	cmat M3 [6][6] = "0,0,0,0,0,0; 0,0,0,0,0,0; -1,0,1,0,0,-1; 0,0,0,2,0,0; 2,0,0,0,0,0; 0,0,0,0,6,0";

	ParamSurf surface1 = ParamSurf(Color(0,1,0),M0,M1,M2,M3);
Ray rayon = Ray(

	surface1.
	return 0; 
}

