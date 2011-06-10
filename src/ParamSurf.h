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
#include "Set.h"
#include "Ray.h"

#include <itpp/itbase.h>

using namespace itpp;
using namespace std;


class ParamSurf : public Shape {
public:
	Color color;
	cmat M0, M1, M2, M3;

	ParamSurf (const Color &_color, cmat M0, cmat M1, cmat M2, cmat M3);
	virtual ~ParamSurf();

	Vector3 normal (const Vector3& pt) const;

	cvec intersect ( const Ray& r ) const;
	
	Set<cmat> make_pencil (const Ray& r) const;

};

#endif /* PARAMSURF_H_ */
