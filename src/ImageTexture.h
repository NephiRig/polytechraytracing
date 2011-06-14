/*
 * ImageTexture.h
 *
 *  Created on: 12 juin 2011
 *      Author: michelet
 */

#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture {
public:
	Image *image;

	ImageTexture(char* file_name);
	virtual ~ImageTexture();

	Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* IMAGETEXTURE_H_ */
