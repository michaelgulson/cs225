#include <iostream>
#include <stdlib.h>
#include "Image.h"
#include "StickerSheet.h"

using cs225::Image;
using cs225::StickerSheet;


int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
Image result;
Image grainger;
grainger.readFromFile("tests/GraingerWhite.png");
Image michael;
michael.readFromFile("tests/MichaelGulson150.png");
Image aws;
aws.readFromFile("tests/AWS-logo-150.png");
Image python;
python.readFromFile("tests/python-logo-150.png");

StickerSheet s1(grainger, 5);
s1.addSticker(michael, 150, 5);
s1.addSticker(aws, 450, 5);
s1.addSticker(python, 750, 5);

result=s1.render();
result.writeToFile("grainger-result.png");
}
