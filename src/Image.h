#ifndef IMAGE_H_
#define IMAGE_H_

#include "Color.h"
#include <math.h>
#include <cstdlib>
#include <iostream>

class Image  
{
public:

   Image() {}
   Image(int _w, int _h);
   Image(int _w, int _h , Color c);
   void safeSetPixel(int x, int y, Color c)
   {
      if (x >= 0 && x < w && y >= 0 && y < h)
         data[x][y] = c; 
   }
   void setPixel(int x, int y, Color c)
   {
      if (!(x >= 0 && x < w && y >= 0 && y < h))
      {
         std::cerr << "Image::setPixel    w = " << w << " h = " << h
              << "     requested pixel (" << x << ", " << y << ")" 
              << std::endl;
         exit(0);
      }
      data[x][y] = c;
   }

   Color getPixel(int x, int y) const
   {
      x = ( x >= 0 ? x : 0);  
      x = ( x <  w ? x : w-1);  
      y = ( y >= 0 ? y : 0);  
      y = ( y <  h ? y : h-1);  
/*      if (!(x >= 0 && x < w && y >= 0 && y < h))
      {
         cerr << "Image::getPixel w = " << w << " h = " << h << endl
            << "       requested pixel (" << x << ", " << y << ")" 
            << endl;
         exit(0);
      }
*/      
      return data[x][y]; 
   }
   int width()  const { return w; }
   int height() const { return h; }
   //void readPPM (char* file_name);
   void writePPM(std::ostream& s) const;

private:
   Color **data;
   int w, h;
};


#endif
