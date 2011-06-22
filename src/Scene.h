#ifndef SCENE_H_
#define SCENE_H_

#include "LightSource.h"
#include "Shape.h"
#include "Sphere.h"
#include "Set.h"
#include "Color.h"

class Scene {
public:
	Set<LightSource*> *_lightSources;
	Set<Shape*> *_shapes;
	Vector3 _observer, _wayUp, _aimedPoint;
	double _distScreen;
	Color L_a;

	Scene(Set<Shape*> *shapes, Set<LightSource*> *lightSources, const Vector3 &obs,
			const Vector3& wayUp, const Vector3& ap, double dist);
	Scene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
