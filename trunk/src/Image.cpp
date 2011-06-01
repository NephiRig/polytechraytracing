#include "Image.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iostream> // debug
#include <cassert>

Image::Image(int w_, int h_ ) : w(w_), h(h_) {
    //assert(w > 0 && h > 0);
    data = new Color*[w];
    //assert(data != 0);
    for (int i = 0; i < w; i++) {
        data[i] = new Color[h];
        //assert(data[i]);
    }
}

Image::Image(int _w, int _h, Color c)
{
	this->w = _w;
	this->h = _h;
	//std::cerr << "params à la construction : _w" << _w << ";_h" << _h << std::endl;
	//std::cerr << "à la construction : w" << this->w << ";h" << this->h << std::endl;
    assert (this->w > 0 && this->h > 0);
	this->data = new Color*[this->w];
    assert(this->data != 0);
    for (int i = 0; i < this->w; i++) {
    	this->data[i] = new Color[this->h];
        assert(data[i]);
        for (int j = 0; j < this->h; j++)
        	this->data[i][j] = c;
    }
    //std::cerr << "apres la construction : w" << this->w << ";h" << this->h << std::endl;
    //std::cerr << "2 apres la construction : _w" << _w << ";_h" << _h << std::endl;
}
/*
void Image::readPPM (char* file_name)
{
   int i, j;
   ifstream in;
   in.open(file_name);
   if (!in)
   {
      cerr << "ERROR -- Can't find PPM file  \'" << string(file_name) << "\'\n";
      exit(0);
   }
   string file_type, garbage;
   Color pix_col;
   
   // read in ppm header info
   in >> file_type >> w >> h >> garbage;
   
   // create new raster with correct size 
   data = new Color*[w];
   for (i = 0; i < w; i++)
      data[i] = new rgb[h];

   // now read in pixel rgb values and assign to raster
   if (file_type == "P3")
   {
      int red, green, blue;
      for (i = h-1; i >= 0; i--)
         for (j = 0; j < w; j++)
         {
            in >> red >> green >> blue;
            pix_col[0] = ((float(red)   + 0.5) / 256.0) * 
                         ((float(red)   + 0.5) / 256.0);
            pix_col[1] = ((float(green) + 0.5) / 256.0) * 
                         ((float(green) + 0.5) / 256.0);
            pix_col[2] = ((float(blue)  + 0.5) / 256.0) * 
                         ((float(blue)  + 0.5) / 256.0);

            data[j][i] = pix_col;
         }
   }
   else
   {
      unsigned char red, green, blue;
      in.get(red); // get rid of newline
      for (i = h-1; i >= 0; i--)
         for (j = 0; j < w; j++)
         {
            in.get(red);
            in.get(green);
            in.get(blue);
               
            pix_col[0] = ((float(red)   + 0.5) / 256.0) * 
                         ((float(red)   + 0.5) / 256.0);
            pix_col[1] = ((float(green) + 0.5) / 256.0) * 
                         ((float(green) + 0.5) / 256.0);
            pix_col[2] = ((float(blue)  + 0.5) / 256.0) * 
                         ((float(blue)  + 0.5) / 256.0);
      
            data[j][i] = pix_col;
         }
   }
}
*/
void Image::writePPM(std::ostream& s) const {
	//std::cerr << "AAAALLLLOOOO" << std::endl;
    s << "P6\n" << w << " " << h << "\n255\n";
    //std::cerr << "P6\n" << w << " " << h << "\n255\n";
    unsigned int i;
    for (int y = h-1; y >= 0; y--) 
        for (int x = 0; x < w; x++) {
           float gamma = 1.0/2.2;
           data[x][y] = Color( pow(data[x][y][0],gamma),
                             pow(data[x][y][1],gamma),
                             pow(data[x][y][2],gamma));
           i = (unsigned int)(256.0 * data[x][y][0]);
           if (i > 255) i = 255;  
           s.put( (unsigned char) i );
           i = (unsigned int)(256.0 * data[x][y][1]);
           if (i > 255) i = 255;  
           s.put( (unsigned char) i );
           i = (unsigned int)(256.0 * data[x][y][2]);
           if (i > 255) i = 255;  
           s.put( (unsigned char) i );
        }
}

