#ifndef IMAGE_H_
#define IMAGE_H_

/**
 * \file Image.h
 * \brief Image creator
 * \author Quentin Grimaud, Michael Gygli, Valentin Michelet
 * \version 0.7
 * \date June 2011
 *
 * Program to create images from pixels color.
 *
 */
#include "Color.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <string>

/**
 * \class Image
 * \brief image creator class
 *
 * Create images from pixels color.<br />
 * Images format is PPM, but it can be easily changed using a convert tool.
 */
class Image {
public:
	Color **_data;	/*!< array of array: stocks each pixel color */
	int _width;		/*!< image width */
	int _height;	/*!< image height */

	/**
	 * \brief Constructor
	 *
	 * Image class constructor from width and height values
	 *
	 * \param width: width value
	 * \param height: height value
	 */
	Image(int width = 0, int height = 0);

	/**
	 * \brief Constructor
	 *
	 * Image class constructor from width, height and global color values
	 *
	 * \param width: width value
	 * \param height: height value
	 * \param color: color value
	 */
	Image(int width, int height, Color color);

	/**
	 * \brief Constructor
	 *
	 * Image class constructor from another image
	 *
	 * \param imageSource: the image source
	 */
	Image(const Image *imageSource);

	/**
	 * \brief Destructor
	 *
	 * Image class destructor
	 */
	virtual ~Image();

	/**
	 * \brief Set pixel
	 *
	 * Change the color of the pixel at x and y coordinates
	 *
	 * \param x: the x coordinate
	 * \param y: the y coordinate
	 * \param color: the new color
	 */
	void setPixel(int x, int y, Color color);

	/**
	 * \brief Get pixel
	 *
	 * Get the color of the pixel at x and y coordinates
	 *
	 * \param x: the x coordinate
	 * \param y: the y coordinate
	 * \return the color of the pixel at x and y coordinates
	 */
	Color getPixel(int x, int y) const;

	/**
	 * \brief operator ==
	 *
	 * Compare two images, that means compare the color of each pixel
	 *
	 * \param image1: the first image
	 * \param image2: the second image
	 * \return true if the two images are identical
	 */
	friend bool operator==(const Image &image1, const Image &image2);

	/**
	 * \brief operator !=
	 *
	 * Compare two images, that means compare the color of each pixel
	 *
	 * \param image1: the first image
	 * \param image2: the second image
	 * \return true if the two images are different
	 */
	friend bool operator!=(const Image &image1, const Image &image2);

	/**
	 * \brief write image
	 *
	 * Create a PPM image from pixels stocked in the double array _data and save it with
	 *
	 * \param os: the ouput stram where to write the image
	 */
	void writePPM(std::ostream &os) const;

	/**
	 * \brief read image
	 *
	 * Stock each pixel of the specified PPM image in the double array _data
	 *
	 * \param fileName: the path of the PPM image
	 */
	void readPPM (std::string fileName);

	/**
	 * \brief read image
	 *
	 * Stock each pixel of the specified PPM image in the double array _data but like a mirror, used in mapping texture
	 *
	 * \param fileName: the path of the PPM image
	 */
	void readReversePPM (std::string fileName);

	/**
	 * \brief print image
	 *
	 * Write the image to create a PPM image whose name is the specified file name
	 *
	 * \param fileName: the name of the PPM image created
	 */
	void printImage(const char* fileName) const;
};

#endif /* IMAGE_H_ */
