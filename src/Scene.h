#ifndef SCENE_H_
#define SCENE_H_

#include "LightSource.h"
#include "Shape.h"
#include "Sphere.h"
#include "Set.h"
#include "Color.h"

class Scene {
public:
	Set<LightSource*>* lightSources;
	Set<Shape*>* shapes;
	Vector3 observer, wayUp, aimedPoint;
	double distScreen;
	Color L_a;

	Scene(Set<Shape*>* sh, Set<LightSource*>* ls, const Vector3& obs,
			const Vector3& wayUp, const Vector3& ap, double dist);
	Scene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
