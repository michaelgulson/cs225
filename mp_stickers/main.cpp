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
  int oneThirdWidth;
  int oneThirdHeight;
  Image result, alma, I;
  alma.readFromFile("alma.png");
  I.readFromFile("i.png");

  oneThirdWidth = alma.width()/3;
  oneThirdHeight = alma.height()/3;

  StickerSheet myStickers(alma, 3);
  for(int i=0; i<3; i++){
    myStickers.addSticker(I,i*oneThirdWidth,i*oneThirdHeight);
  }

  result = myStickers.render();
  result.writeToFile("myImage.png");

  //deconstructor
//  delete myStickers;
//  delete alma;
//  delete I;
  return 0;
}
