/*
 * Texture.h
 *
 *  Created on: 12 juin 2011
 *      Author: michelet
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

class Texture {
public:
	Texture();
	virtual ~Texture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const = 0;
};

#endif /* TEXTURE_H_ */
