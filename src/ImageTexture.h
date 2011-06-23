#ifndef IMAGETEXTURE_H_
#define IMAGETEXTURE_H_

#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture {
public:
	Image *image;

	ImageTexture(std::string file_name);
	virtual ~ImageTexture();

	virtual Color value(const Vector2 &uv, const Vector3 &p) const;
};

#endif /* IMAGETEXTURE_H_ */
