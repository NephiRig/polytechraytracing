/*
 * ParamSurf.h
 *
 *  Created on: 31 mai 2011
 *      Author: Sandra & Marion
 */

#ifndef PARAMSURF_H_
#define PARAMSURF_H_

#include "Shape.h"
#include "Material.h"
#include "Vector3.h"
#include "Color.h"

class ParamSurf : public Shape {
public:
	Color color;
	int [][] M0, M1, M2, M3;

	ParamSurf (const Color &_color, int [][] M0, int [][] M1, int [][] M2, int [][] M3);
	virtual ~ParamSurf();

	Vector3 normal (const Vector3& pt) const;

	Set<Vector3> intersect ( const Ray& r ) const;
	
	Set<Vector3> pencil(const Ray& r) const {


};

#endif /* PARAMSURF_H_ */
