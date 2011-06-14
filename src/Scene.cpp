/*
 * Scene.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Scene.h"

Scene::Scene ( Set<Shape*>* sh, Set<LightSource*>* ls, const Vector3& obs,
	const Vector3& _wayUp, const Vector3& ap, double dist)
{
	lightSources = ls;
	shapes = sh;
	observer = obs;
	wayUp = _wayUp;
	aimedPoint = ap;
	distScreen = dist;

}

Scene::Scene (){

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}
