/*
 * ImageTexture.cpp
 *
 *  Created on: 12 juin 2011
 *      Author: michelet
 */

#include "ImageTexture.h"

ImageTexture::ImageTexture(char* file_name) {
	cerr << "coucou1" << endl;
	image = new Image();
	image->readPPM(file_name);
	cerr << "coucou4" << endl;
}

ImageTexture::~ImageTexture() {
	// TODO Auto-generated destructor stub
}

Color ImageTexture::value(const Vector2 &uv, const Vector3 &p) const {
	float u = uv.get_x() - int(uv.get_x());
	float v = uv.get_y() - int(uv.get_y());

	u *= (image->width() - 3);
	v *= (image->height() - 3);

	int iu = (int) u;
	int iv = (int) v;

	float tu = u - iu;
	float tv = v - iv;

	Color c = image->getPixel(iu, iv) * (1 - tu) * (1 - tv) +
			image->getPixel(iu + 1, iv) * tu * (1 - tv) +
			image->getPixel(iu, iv + 1) * (1 - tu) * tv +
			image->getPixel(iu + 1, iv + 1) * tu * tv;

	return c;
}
