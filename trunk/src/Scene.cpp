#include "Scene.h"

Scene::Scene(Set<Shape*> *shapes, Set<LightSource*> *lightSources,
		const Vector3 &observer, const Vector3& wayUp,
		const Vector3& aimedPoint, double distScreen) :
	_lightSources(lightSources), _shapes(shapes), _observer(observer),
	_wayUp(wayUp), _aimedPoint(aimedPoint), _distScreen(distScreen) {
}

Scene::Scene() {
}

Scene::~Scene() {
}
