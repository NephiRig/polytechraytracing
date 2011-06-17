#include "Image.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream> // debug
#include <cassert>

Image::Image(int _w, int _h) :
	w(_w), h(_h) {
	data = new Color*[w];
	for (int i = 0; i < w; i++) {
		data[i] = new Color[h];
	}
}

Image::Image(int _w, int _h, Color c) {
	this->w = _w;
	this->h = _h;
	assert (this->w > 0 && this->h > 0);
	this->data = new Color*[this->w];
	assert(this->data != 0);
	for (int i = 0; i < this->w; i++) {
		this->data[i] = new Color[this->h];
		assert(data[i]);
		for (int j = 0; j < this->h; j++) {
			this->data[i][j] = c;
		}
	}
}

int Image::width() const {
	return w;
}

int Image::height() const {
	return h;
}

void Image::safeSetPixel(int x, int y, Color c) {
	if (x >= 0 && x < w && y >= 0 && y < h)
		data[x][y] = c;
}

void Image::setPixel(int x, int y, Color c) {
	if (x >= 0 && x < w && y >= 0 && y < h) {
		data[x][y] = c;
	}
}

Color Image::getPixel(int x, int y) const {
	x = (x >= 0 ? x : 0);
	x = (x < w ? x : w - 1);
	y = (y >= 0 ? y : 0);
	y = (y < h ? y : h - 1);
	return data[x][y];
}

void Image::writePPM(std::ostream &s) const {
	s << "P6\n" << w << " " << h << "\n255\n";
	unsigned int i;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			double gamma = 1.0 / 2.2;
			data[x][y] = Color(pow(data[x][y][0], gamma), pow(data[x][y][1],
					gamma), pow(data[x][y][2], gamma));
			i = (unsigned int) (256.0 * data[x][y][0]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * data[x][y][1]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * data[x][y][2]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
		}
}

void Image::readPPM(std::string file_name) {
	std::ifstream in;
	in.open(file_name.c_str());
	if (!in.is_open()) {
		std::cerr << "Can't open file \'" << file_name << "\'.\n";
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int i, j, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	w = cols;
	h = rows;

	data = new Color*[w];
	for (i = 0; i < w; i++)
		data[i] = new Color[h];

	in.get(ch);

	for (i = h-1; i >= 0; i--) {
		for (j = 0; j < w; j++) {
			in.get(red);
			in.get(green);
			in.get(blue);
			data[i][j] = Color(
					(float) ((unsigned char)red)/255.0,
					(float) ((unsigned char)green)/255.0,
					(float) ((unsigned char)blue)/255.0);
		}
	}
}
