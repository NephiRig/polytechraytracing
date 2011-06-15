
#include <cmath>
#include <iostream> // debug

#include "ScreenV2.h"

ScreenV2::ScreenV2 ( const Vector3& _observer, const Vector3& _wayUp,
	const Vector3& _aimedPoint, double _viewAngle, int _width2D, int _height2D )
	: initialized(false), observer(_observer),
	aimedPoint(_aimedPoint), viewAngle(_viewAngle),
	w2D(_width2D), h2D(_height2D)
{
	wayUp = _wayUp.normalized ();
}

ScreenV2::~ScreenV2(){}

bool ScreenV2::initFromWH3D ( double _width3D, double _height3D )
{
	double t_va = tan ( viewAngle );
	if ( t_va < 0.05 && t_va > - 0.05 ) // TODO: find a proper epsilon
		return false;
	w3D = _width3D;
	h3D = _height3D;
	ratioWH = w3D / h3D;
	distScreen = w3D/(2.0*t_va);
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize ();
}

/*
bool ScreenV2::initFromDistScreen ( double _distScreen, double _ratioWH )
{
	double t_va = tan ( viewAngle );
	if ( t_va < 0.05 && t_va > - 0.05 ) // TODO: find a proper epsilon
		return false;
	distScreen = _distScreen;
	ratioWH = _ratioWH;
	w3D = 2*distScreen*t_va;
	h3D = w3D/ratioWH;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize ();
}
*/
bool ScreenV2::initFromDistScreen ( double _distScreen )
{
	double t_va = tan ( viewAngle );
	std::cerr << "t_va: " << t_va << std::endl;
	if ( t_va < 0.05 && t_va > - 0.05 ) // TODO: find a proper epsilon
		return false;
	distScreen = _distScreen;
	ratioWH = w2D*1.0/h2D;
	w3D = 2*distScreen*t_va;
	h3D = w3D/ratioWH;
	std::cerr << "w3D: " << w3D << std::endl;
	std::cerr << "h3D: " << h3D << std::endl;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	return initialize ();
}

bool ScreenV2::initialize ()
{
	double t_va = tan ( viewAngle );
	if ( t_va < 0.05 && t_va > - 0.05 ) // TODO: find a proper epsilon
		return false;
	// now that distScreen, w3D, h3D, and ratioHW are set, we have to set screen3D[] and initialized
	Vector3 AV = aimedPoint - observer; // AV is the vector from the observer to the aimed point
	Vector3 dir = AV.normalize ();
	distScreen = w3D/(2.0*t_va);
	Vector3 B = observer + distScreen * dir; // B is the center of the screen
	Vector3 cp = cross_product ( AV, wayUp ).normalize (); // the third direction: from the center to the right of the screen
	Vector3 temp = (w3D/2.0)*cp;
	Vector3 N = B + temp; // N is the point at the center-right of the screen
	Vector3 M = B - temp; // M is the point at the center-left of the screen
	temp = (h3D/2.0)*wayUp;
	screen3D[0] = M + temp; // top-left, top-right, bottom-left, bottom-right corners of the screen
	screen3D[1] = N + temp;
	screen3D[2] = M - temp;
	screen3D[3] = N - temp;
	std::cerr << "screen3D[0]: " << screen3D[0] << std::endl;
	std::cerr << "screen3D[1]: " << screen3D[1] << std::endl;
	std::cerr << "screen3D[2]: " << screen3D[2] << std::endl;
	std::cerr << "screen3D[3]: " << screen3D[3] << std::endl;
	initialized = true;
	return initialized;
}

Vector3 ScreenV2::getPixel ( double x, double y )
{ // TODO: maybe we should optimize our class data structure to ease this operation
	return screen3D[0] + (x*1.0/w2D)*(screen3D[1]-screen3D[0])
		+ (y*1.0/h2D)*(screen3D[2]-screen3D[0]);
}
Vector3 ScreenV2::getPixel ( const Vector2& pt )
{
	return screen3D[0] + (pt[0]*1.0/w2D)*(screen3D[1]-screen3D[0])
		+ (pt[1]*1.0/h2D)*(screen3D[2]-screen3D[0]);
}

