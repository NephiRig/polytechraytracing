#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

using namespace std;

class Image {
public:
	Image() {}
	Image(int _w, int _h);
	Image(int _w, int _h, Color c);

	int width() const;
	int height() const;

	void safeSetPixel(int x, int y, Color c);
	void setPixel(int x, int y, Color c);

	Color getPixel(int x, int y) const;

	void writePPM(ostream &s) const;
	void readPPM (string file_name);

private:
	Color **data;
	int w, h;
};

#endif