#include "SceneParser.h"

SceneParser::SceneParser(char* fileName) :
	_fileName(fileName) {
	_screenHeight = 480;
	_screenWidth = 640;
	_oversampling = 1;
	parse();
}

SceneParser::~SceneParser() {
}

int SceneParser::parse() {
	TiXmlDocument scene(_fileName);
	if (!scene.LoadFile()) {
		std::cerr << "error while loading" << std::endl;
		std::cerr << "error #" << scene.ErrorId() << " : " << scene.ErrorDesc() << std::endl;
		return -1;
	} else {
		std::cout << "################################################" << std::endl;
		std::cout << "BEGINNING OF XML PARSING" << std::endl;
		TiXmlHandle hdl(&scene);
		TiXmlElement *elem = hdl.FirstChildElement().FirstChildElement().Element();
		if (!elem) {
			std::cerr << "The node to reach does not exist" << std::endl;
			return -1;
		}

		//Browse every node
		while (elem) {
			//Screen setup
			if ((std::string) elem->Value() == "screenSetup") {
				elem->QueryIntAttribute("width", &_screenWidth);
				elem->QueryIntAttribute("height", &_screenHeight);
				elem->QueryIntAttribute("overSampling", &_oversampling);
			} else if ((std::string) elem->Value() == "shape") { //If it's a shape
				std::string shapeType = elem->Attribute("type");
				Shape *s;
				Color color;
				Material material;
				elem->FirstChildElement("color")->QueryDoubleAttribute("r", &color[0]);
				elem->FirstChildElement("color")->QueryDoubleAttribute("g", &color[1]);
				elem->FirstChildElement("color")->QueryDoubleAttribute("b", &color[2]);
				elem->FirstChildElement("material")->QueryDoubleAttribute("ka", &material.k_a);
				elem->FirstChildElement("material")->QueryDoubleAttribute("kd", &material.k_d);
				elem->FirstChildElement("material")->QueryDoubleAttribute("ks", &material.k_s);
				elem->FirstChildElement("material")->QueryDoubleAttribute("ns", &material.n_s);
				elem->FirstChildElement("material")->QueryDoubleAttribute("kreflex", &material.k_reflex);
				if (shapeType == "uvsphere" || shapeType == "sphere") {
					Vector3 center;
					double radius;
					elem->FirstChildElement("center")->QueryDoubleAttribute("x", &center[0]);
					elem->FirstChildElement("center")->QueryDoubleAttribute("y", &center[1]);
					elem->FirstChildElement("center")->QueryDoubleAttribute("z", &center[2]);
					elem->FirstChildElement("radius")->QueryDoubleAttribute("value", &radius);
					if (shapeType == "uvsphere") {
						ImageTexture *image;
						double plusPhi;
						double plusTheta;
						std::string typeTexture = elem->FirstChildElement("texture")->Attribute("type");
						if (typeTexture == "image") {
							image = new ImageTexture((std::string)elem->FirstChildElement("texture")->FirstChildElement("src")->Attribute("value"));

						}
						elem->FirstChildElement("plusphi")->QueryDoubleAttribute("value", &plusPhi);
						plusPhi *= M_PI;
						elem->FirstChildElement("plustheta")->QueryDoubleAttribute("value", &plusTheta);
						plusTheta *= M_PI;
						s = new UVSphere(color, material, center, radius, image, plusTheta, plusPhi);
					} else if (shapeType == "sphere") {
						s = new Sphere(color, material, center, radius);
					}
				} else if (shapeType == "draughtboard" || shapeType == "rectangle" || shapeType == "plane") {
					Ray normAndPoint;
					elem->FirstChildElement("center")->QueryDoubleAttribute("x", &normAndPoint[0][0]);
					elem->FirstChildElement("center")->QueryDoubleAttribute("y", &normAndPoint[0][1]);
					elem->FirstChildElement("center")->QueryDoubleAttribute("z", &normAndPoint[0][2]);
					elem->FirstChildElement("normal")->QueryDoubleAttribute("x", &normAndPoint[1][0]);
					elem->FirstChildElement("normal")->QueryDoubleAttribute("y", &normAndPoint[1][1]);
					elem->FirstChildElement("normal")->QueryDoubleAttribute("z", &normAndPoint[1][2]);
					if (shapeType == "plane") {
						s = new Plane(color, material, normAndPoint);
					} else if (shapeType == "draughtboard" || shapeType == "rectangle") {
						double height;
						double width;
						elem->FirstChildElement("height")->QueryDoubleAttribute("value", &height);
						elem->FirstChildElement("width")->QueryDoubleAttribute("value", &width);
						if (shapeType == "rectangle") {
							s = new Rectangle(color, material, normAndPoint, height, width);
						} else if (shapeType == "draughtboard") {
							Color colorD;
							double caseSize;
							elem->FirstChildElement("otherColor")->QueryDoubleAttribute("r", &colorD[0]);
							elem->FirstChildElement("otherColor")->QueryDoubleAttribute("g", &colorD[1]);
							elem->FirstChildElement("otherColor")->QueryDoubleAttribute("b", &colorD[2]);
							elem->FirstChildElement("caseSize")->QueryDoubleAttribute("value", &caseSize);
							s = new Draughtboard(color, material, colorD, normAndPoint, height, width, caseSize);
						}
					}
				} else {
					std::cout << "Invalid description: " << shapeType << " does not exist.\nPlease, check the spelling and try again." << std::endl;
					return -1;
				}
				_shapes.add(s);
				std::cout << "Shape #" << _shapes.size() << " (" << shapeType << ")" << " INITIALIZED" << std::endl;
			} else if ((std::string) elem->Value() == "light") {
				double intensity;
				Vector3 position;
				Color color;
				elem->FirstChildElement("intensity")->QueryDoubleAttribute("value", &intensity);
				elem->FirstChildElement("position")->QueryDoubleAttribute("x", &position.coords[0]);
				elem->FirstChildElement("position")->QueryDoubleAttribute("y", &position.coords[1]);
				elem->FirstChildElement("position")->QueryDoubleAttribute("z", &position.coords[2]);
				elem->FirstChildElement("color")->QueryDoubleAttribute("r", &color.val[0]);
				elem->FirstChildElement("color")->QueryDoubleAttribute("g", &color.val[1]);
				elem->FirstChildElement("color")->QueryDoubleAttribute("b", &color.val[2]);
				LightSource *l = new LightSource(intensity, position, color);
				_lightSources.add(l);
				std::cerr << "Light #" << _lightSources.size() << " INITIALIZED" << std::endl;
			} else {
				std::cout << "Invalid description: " << (std::string) elem->Value() << " does not exist.\nPlease, check the spelling and try again." << std::endl;
				return -1;
			}
			//FIXME finir le parser avec les données de la camera
			elem = elem->NextSiblingElement(); // iteration
		}
		std::cout << "ENDING OF XML PARSING" << std::endl;
		std::cout << "################################################\n" << std::endl;
	}
	return 0;
}
