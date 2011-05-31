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
#include "Set.h"

class Scene {
public:
	Scene();
	virtual ~Scene();

	//Set<LightSource> lightSources;
	//Set<Shape> shapes;;
};

#endif /* SCENE_H_ */
