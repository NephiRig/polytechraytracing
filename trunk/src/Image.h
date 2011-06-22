#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

class Image {
public:
	Color **_data;
	int _w, _h;

	Image() {}
	Image(int w, int h);
	Image(int w, int h, Color c);
	Image(const Image *source);

	int width() const;
	int height() const;

	void setPixel(int x, int y, Color c);

	Color getPixel(int x, int y) const;

	friend bool operator==(const Image &img1, const Image &img2);
	friend bool operator!=(const Image &img1, const Image &img2);

	void writePPM(std::ostream &s) const;
	void readPPM (std::string fileName);

	void printImage(const char* fileName) const;
};

#endif /* IMAGE_H_ */
