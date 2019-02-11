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
  printf("%d\n", oneThirdWidth);
  printf("%d\n", oneThirdHeight);

  StickerSheet myStickers(alma, 3);
  for(int i=0; i<3; i++){
    if(myStickers.addSticker(I,i*oneThirdWidth,i*oneThirdHeight)==-1)
      printf("Error adding sticker\n");
  }

  result = myStickers.render();
  result.writeToFile("myImage.png");

  //deconstructor
//  delete myStickers;
//  delete alma;
//  delete I;
  return 0;
}
