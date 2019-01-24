#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
using cs225::HSLAPixel;
using cs225::PNG;

void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG png, png2;
  png.readFromFile(inputFile);
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

  return png;
}
