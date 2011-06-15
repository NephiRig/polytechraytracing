
#ifndef SCREENV2_H_
#define SCREENV2_H_

#include "Vector3.h"
#include "Vector2.h"

class ScreenV2 {
public:
	Vector3 observer;
	Vector3 aimedPoint;
	Vector3 wayUp;
	double viewAngle; // TODO: that's in fact the half of the angle
	double distScreen;
	double w3D;
	double h3D;
	double ratioWH; // for 2D and 3D
	Vector3 screen3D[4]; // top-left, top-right, bottom-left, bottom-right corners of the screen
	bool initialized;
	int w2D;
	int h2D;

	ScreenV2 ( const Vector3& _observer, const Vector3& _wayUp,
		const Vector3& _aimedPoint, double _viewAngle, int _width2D, int _height2D );
	virtual ~ScreenV2();

	bool initFromWH3D ( double _width3D, double _height3D );
	/*bool initFromDistScreen ( double _distScreen, double _ratioWH );*/
	bool initFromDistScreen ( double _distScreen );

	Vector3 getPixel ( double x, double y ); // returns the 3D point where the pixel is
	Vector3 getPixel ( const Vector2& pt );
protected:
	bool initialize ();
};

#endif /* SCREENV2_H_ */
