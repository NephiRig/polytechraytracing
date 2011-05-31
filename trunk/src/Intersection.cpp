/*
 * Intersection.cpp
 *
 *  Created on: 31 mai 2011
 *      Author: quentin
 */

#include "Intersection.h"

Intersection::Intersection (Vector3 _pt, Shape* _sh/*= NULL*/ )
	: pt(_pt), sh(_sh)
{}

Intersection::~Intersection()
{
	// TODO Auto-generated destructor stub
}
