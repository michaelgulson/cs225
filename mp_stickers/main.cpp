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
/*  int oneThirdWidth;
  int oneThirdHeight;
  Image result, alma, I;
  alma.readFromFile("alma.png");
  I.readFromFile("i.png");

  oneThirdWidth = alma.width()/3;
  oneThirdHeight = alma.height()/3;
  printf("%d\n", oneThirdWidth);
  printf("%d\n", oneThirdHeight);

  StickerSheet myStickers(alma, 3);
  for(int i=0; i<2; i++){
    if(myStickers.addSticker(I,i*oneThirdWidth,i*oneThirdHeight)==-1)
      printf("Error adding sticker\n");
  }
  if(myStickers.addSticker(I, 2*oneThirdWidth, 0*oneThirdHeight)==-1)
    printf("Error adding sticker\n");

  result = myStickers.render();
  result.writeToFile("myImage.png");

*/
/*
Image alma;
alma.readFromFile("tests/alma.png");
Image i;
i.readFromFile("tests/i.png");

StickerSheet sheet(alma, 1);
sheet.addSticker(i, 20, 200);

sheet.changeMaxStickers(2);
sheet.addSticker(i, 40, 200);

Image expected,result;
expected.readFromFile("tests/expected-2.png");

result=sheet.render();
if(result==expected){
  printf("test case1 passed");
}
else{
  result.writeToFile("testcase1_result.png");
  expected.writeToFile("testcase1_expected.png");
}
*/
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

// StickerSheet s2(s1);
// s2.removeSticker(1);

// Image result1, result2;

// result1 = s1.render();
// result2 = s2.render();
// if(result1 == expected2 ){
//   printf("testpt1 passed\n");
// }
// if(result2 == expected){
//   printf("testpt2 passed\n");

// }
//REQUIRE(== expected );


}
//Testcase 2
/*


//  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  Image expected;
  expected.readFromFile("tests/expected.png");

  //REQUIRE( sheet.render() == expected );
//}


//TEST_CASE("StickerSheet::changeMaxStickers() does not discard stickers when resized larger", "[weight=1][part=2]") {
  //Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(7);

  Image expected;
  expected.readFromFile("tests/expected.png");

  //REQUIRE( sheet.render() == expected );
//}
//
//TEST_CASE("StickerSheet::changeMaxStickers() does not discard original stickers when resized smaller", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(3);

  Image expected;
  expected.readFromFile("tests/expected.png");

//  REQUIRE( sheet.render() == expected );
//}

//TEST_CASE("StickerSheet::changeMaxStickers() can increase the number of stickers on an image", "[weight=1][part=2]") {
  Image alma; alma.readFromFile("tests/alma.png");
  Image i;    i.readFromFile("tests/i.png");

  StickerSheet sheet(alma, 1);
  sheet.addSticker(i, 20, 200);

  sheet.changeMaxStickers(2);
  sheet.addSticker(i, 40, 200);

  Image expected;
  expected.readFromFile("tests/expected-2.png");

//  REQUIRE( sheet.render() == expected );
//}

//TEST_CASE("StickerSheet::changeMaxStickers() discards stickers beyond the end of a smaller StickerSheet", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.changeMaxStickers(1);

//  REQUIRE( sheet.render() == expected );
//}



//
// test removeSticker
//
//TEST_CASE("StickerSheet::removeSticker() can remove the last sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(1);

//  REQUIRE( sheet.render() == expected );
//}

//TEST_CASE("StickerSheet::removeSticker() can remove the first sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.removeSticker(0);

//  REQUIRE( sheet.render() == expected );
//}

//TEST_CASE("StickerSheet::removeSticker() can remove all stickers", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 80, 200);
  sheet.removeSticker(2);
  sheet.removeSticker(1);
  sheet.removeSticker(0);

//  REQUIRE( sheet.render() == alma );
//}



//
// test that getSticker works
//
//TEST_CASE("StickerSheet::getSticker() returns the sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

  REQUIRE( *(sheet.getSticker(0)) == i );
}

TEST_CASE("StickerSheet::getSticker() returns NULL for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);

//  REQUIRE( sheet.getSticker(1) == NULL );
//}

//TEST_CASE("StickerSheet::getSticker() returns NULL for a removed sticker", "[weight=1][part=2]") {
  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");
  Image expected;
  expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 50, 200);
  sheet.removeSticker(0);

//  REQUIRE( sheet.getSticker(0) == NULL );
//}


//
// translate
//
//TEST_CASE("StickerSheet::translate() translates a sticker's location", "[weight=1][part=2]") {
  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");
  Image expected;
  expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 0, 0);
  sheet.translate(0, 20, 200);

//  REQUIRE( sheet.render() == expected );
//}

//TEST_CASE("StickerSheet::translate() returns false for a non-existant sticker", "[weight=1][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");

  StickerSheet sheet(alma, 5);
  sheet.addSticker(i, 20, 200);

//  REQUIRE( sheet.translate(3, 20, 200) == false );
//}


//
// render
//
//
//TEST_CASE("A complex StickerSheet is correct", "[weight=5][part=2]") {
  Image alma;     alma.readFromFile("tests/alma.png");
  Image i;        i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected-3.png");

  StickerSheet sheet(alma, 100);
  sheet.addSticker(i, 20, 200);
  sheet.addSticker(i, 40, 200);
  sheet.addSticker(i, 60, 200);
  sheet.addSticker(i, 80, 200);
  sheet.addSticker(i, 100, 200);
  sheet.addSticker(i, 120, 200);
  sheet.addSticker(i, 140, 200);
  sheet.removeSticker(3);
  sheet.translate(0, 0, 0);

//  REQUIRE( sheet.render() == expected );
//}


//
// copy ctor
//
//TEST_CASE("StickerSheet's copy constructor makes an independent copy", "[weight=2][part=2]") {
  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(s1);
  s2.removeSticker(1);

//  REQUIRE( s1.render() == expected2 );
//
//}

//TEST_CASE("StickerSheet's assignment operator makes an independent copy", "[weight=2][part=2]") {
  Image alma;
  alma.readFromFile("tests/alma.png");
  Image i;
  i.readFromFile("tests/i.png");
  Image expected; expected.readFromFile("tests/expected.png");
  Image expected2; expected2.readFromFile("tests/expected-2.png");

  StickerSheet s1(alma, 5);
  s1.addSticker(i, 20, 200);
  s1.addSticker(i, 40, 200);

  StickerSheet s2(alma, 5);
  s2 = s1;
  s2.removeSticker(1);

  //REQUIRE( s1.render() == expected2 );
//  REQUIRE( s2.render() == expected );




  //deconstructor
//  delete myStickers;
//  delete alma;
//  delete I;
  return 0;
}
*/
