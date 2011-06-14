/*
 * Scene.h
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#ifndef SCENE_H_
#define SCENE_H_

#include "LightSource.h"
#include "Shape.h"
#include "Sphere.h"
#include "Set.h"
#include "Color.h"

class Scene {
public:
	Scene ( Set<Shape*>* sh, Set<LightSource*>* ls, const Vector3& obs, const Vector3& wayUp, const Vector3& ap, double dist );
	Scene ();
	virtual ~Scene ();

	Set<LightSource*>* lightSources;
	Set<Shape*>* shapes;
	Vector3 observer, wayUp, aimedPoint;
	double distScreen;
	Color L_a;
};

#endif /* SCENE_H_ */
