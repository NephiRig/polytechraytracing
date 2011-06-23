#include "Image.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream> // debug
#include <cassert>

Image::Image(int w, int h) :
	_w(w), _h(h) {
	this->_data = new Color*[this->_w];
	for (int x = 0; x < this->_w; x++) {
		this->_data[x] = new Color[this->_h];
	}
}

Image::Image(int w, int h, Color c) {
	this->_w = w;
	this->_h = h;
	assert (this->_w > 0 && this->_h > 0);

	this->_data = new Color*[this->_w];
	assert(this->_data != 0);

	for (int x = 0; x < this->_w; x++) {
		this->_data[x] = new Color[this->_h];
		assert(_data[x]);
		for (int y = 0; y < this->_h; y++) {
			this->_data[x][y] = c;
		}
	}
}

Image::Image(const Image *source) {
	this->_w = source->_w;
	this->_h = source->_h;

	this->_data = new Color*[this->_w];
	for (int x = 0; x < this->_w; x++) {
		this->_data[x] = new Color[this->_h];
		for (int y = 0; y < this->_h; y++) {
			this->_data[x][y] = source->getPixel(x, y);
		}
	}
}

int Image::width() const {
	return this->_w;
}

int Image::height() const {
	return this->_h;
}

void Image::setPixel(int x, int y, Color c) {
	if (x >= 0 && x < this->_w && y >= 0 && y < this->_h) {
		this->_data[x][y] = c;
	}
}

Color Image::getPixel(int x, int y) const {
	x = (x >= 0 ? x : 0);
	x = (x < this->_w ? x : this->_w - 1);
	y = (y >= 0 ? y : 0);
	y = (y < this->_h ? y : this->_h - 1);
	return this->_data[x][y];
}

bool operator==(const Image &img1, const Image &img2) {
	int w1 = img1._w;
	int h1 = img1._h;
	int w2 = img1._w;
	int h2 = img1._h;
	if (w1 != w2 || h1 != h2) {
		return false;
	} else {
		for (int y = 0; y < h1; y++) {
			for (int x = 0; x < w1; x++) {
				if (img1._data[x][y] != img2._data[x][y]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool operator!=(const Image &img1, const Image &img2) {
	return !(img1 == img2);
}

void Image::writePPM(std::ostream &s) const {
	s << "P6\n" << this->_w << " " << this->_h << "\n255\n";
	unsigned int i;
	for (int y = 0; y < this->_h; y++) {
		for (int x = 0; x < _w; x++) {
			double gamma = 1.0 / 2.2;
			this->_data[x][y] = Color(pow(this->_data[x][y][0], gamma), pow(this->_data[x][y][1],
					gamma), pow(this->_data[x][y][2], gamma));
			i = (unsigned int) (256.0 * this->_data[x][y][0]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * this->_data[x][y][1]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
			i = (unsigned int) (256.0 * this->_data[x][y][2]);
			if (i > 255)
				i = 255;
			s.put((unsigned char) i);
		}
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
	int x, y, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	this->_w = cols;
	this->_h = rows;

	std::cout << "HELLO " << cols << " " << rows << std::endl;

	this->_data = new Color*[this->_w];
	for (x = 0; x < this->_w; x++) {
		this->_data[x] = new Color[this->_h];
	}

	in.get(ch);

	for (y = 0; y < this->_h; y++) {
		for (x = 0; x < this->_w; x++) {
			in.get(red);
			in.get(green);
			in.get(blue);
			this->_data[x][y] = Color(
					(float) ((unsigned char)red)/255.0,
					(float) ((unsigned char)green)/255.0,
					(float) ((unsigned char)blue)/255.0);
		}
	}
}

void Image::readReversePPM(std::string file_name) {
	std::ifstream in;
	in.open(file_name.c_str());
	if (!in.is_open()) {
		std::cerr << "Can't open file \'" << file_name << "\'.\n";
		exit(-1);
	}

	char ch, type;
	char red, green, blue;
	int x, y, cols, rows;
	int num;

	in.get(ch);
	in.get(type);
	in >> cols >> rows >> num;

	this->_w = cols;
	this->_h = rows;

	std::cout << "HELLO " << cols << " " << rows << std::endl;

	this->_data = new Color*[this->_w];
	for (x = 0; x < this->_w; x++) {
		this->_data[x] = new Color[this->_h];
	}

	in.get(ch);

	for (y = this->_h-1; y >= 0; y--) {
		for (x = 0; x < this->_w; x++) {
			in.get(red);
			in.get(green);
			in.get(blue);
			this->_data[x][y] = Color(
					(float) ((unsigned char)red)/255.0,
					(float) ((unsigned char)green)/255.0,
					(float) ((unsigned char)blue)/255.0);
		}
	}
}

void Image::printImage(const char *fileName) const {
	std::ofstream myfile;
	myfile.open(fileName);
	this->writePPM(myfile);
	myfile.close();
}
