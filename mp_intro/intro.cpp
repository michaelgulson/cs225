#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png;
  png.readFromFile(inputFile);
  cs225::PNG png2(png);
  for (unsigned x = 0; x < png.width(); x++) {
   for (unsigned y = 0; y < png.height(); y++) {
     HSLAPixel & pixelInput = png.getPixel(x, y);
     HSLAPixel & pixelOutput = png2.getPixel(png.width()-x-1,png.height()-y-1);
     pixelOutput.h=pixelInput.h;
     pixelOutput.s= pixelInput.s;
     pixelOutput.l=pixelInput.l;
     pixelOutput.a=pixelInput.a;
   }
  }
  png2.writeToFile(outputFile);


}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for (unsigned x = 0; x < png.width(); x++) {
   for (unsigned y = 0; y < png.height(); y++) {
     HSLAPixel & pixelInput = png.getPixel(x, y);
        if(x==y){
          pixelInput.h=240;
          pixelInput.s=1;
          pixelInput.l=.25;
          pixelInput.a=1.0;
        }
        else if((x<=y+2)&&(x>=y-2)){
          pixelInput.h=180;
          pixelInput.s=1;
          pixelInput.l=.25;
          pixelInput.a=1.0;

        }
        else{
          pixelInput.h=0;
          pixelInput.s=1;
          pixelInput.l=.25;
          pixelInput.a=1.0;
        }
    }
  }

  return png;
}
