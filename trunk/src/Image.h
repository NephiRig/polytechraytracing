#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

class Image {
public:
	Color **data;
	int w, h;

	Image() {}
	Image(int _w, int _h);
	Image(int _w, int _h, Color c);

	int width() const;
	int height() const;

	void safeSetPixel(int x, int y, Color c);
	void setPixel(int x, int y, Color c);

	Color getPixel(int x, int y) const;

	void writePPM(std::ostream &s) const;
	void readPPM (std::string file_name);
};

#endif /* IMAGE_H_ */
