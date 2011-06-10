/*
 * Scene.cpp
 *
 *  Created on: 31.05.2011
 *      Author: nb-gyglim
 */

#include "Scene.h"

Scene::Scene (Set<Shape*> &sh, Set<LightSource*> &ls, Vector3 &obs, Vector3 &ap, double dist){
	lightSources = ls;
	shapes = sh;
	observer = obs;
	aimedPoint = ap;
	distScreen = dist;

}

Scene::Scene (){

}

Scene::~Scene() {
	// TODO Auto-generated destructor stub
}
