#ifndef SCENEPARSER_H_
#define SCENEPARSER_H_

#include <string>

#include "tinyxml.h"

#include "Draughtboard.h"
#include "LightSource.h"
#include "Plane.h"
#include "Rectangle.h"
#include "ScreenV2.h"
#include "Set.h"
#include "ScreenV2.h"
#include "Shape.h"
#include "Sphere.h"
#include "Texture.h"

class SceneParser {
public:
	char* _fileName;
	Set<Shape*> _shapes;
	Set<LightSource*> _lightSources;
	int _screenWidth, _screenHeight, _oversampling;
	//FIXME ajouter la caméra
	//ScreenV2 _camera;

	SceneParser(char* fileName);
	virtual ~SceneParser();

	int parse();
};

#endif /* SCENEPARSER_H_ */
