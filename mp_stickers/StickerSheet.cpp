#include "StickerSheet.h"

//Author: Michael Gulson

//StickerSheet puts other images ontop of a base image.  With one basePicture and an array of images
//This object is used to create one image with the stickers ontop of the basePicture

namespace cs225{
//copies stickersheet
void StickerSheet::_copy(StickerSheet const & other){
  imageArrSize = other.imageArrSize;
  basePicture= other.basePicture;
  imageArr = new Image[imageArrSize];
  xPosition = new int[imageArrSize];
  yPosition = new int[imageArrSize];
  for (int i = 0; i < imageArrSize; i++) {
    imageArr[i] = other.imageArr[i];
    xPosition[i] = other.xPosition[i];
    yPosition[i] = other.yPosition[i];
  }
}

//frees memory associated with stickersheet
void StickerSheet::_destroy(){
  delete [] imageArr;
  delete [] xPosition;
  delete [] yPosition;
}

//copy constructor
StickerSheet::StickerSheet(const Image &picture, unsigned max){

  basePicture = picture;
  imageArr= new Image[max];
  xPosition = new int[max];
  yPosition = new int[max];
  basePicture = picture;
  imageArrSize = max;
  for(unsigned i=0; i<max; i++){
    xPosition[i]=0;
    yPosition[i]=0;
  }
}

//destructor operator
StickerSheet::~StickerSheet(){
  _destroy();
}

//copy constructor by reference
StickerSheet::StickerSheet(const StickerSheet &other){
  _copy(other);
}

//equal operator overload
const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
  _destroy();
  _copy(other);
  return *this;
}

//Changes the maximum stickers allowed on the stickersheet
void 	StickerSheet::changeMaxStickers(unsigned max){
  Image * newimageArr = new Image[max];
  int * newxPosition = new int[max];
  int * newyPosition = new int[max];

  Image emptyImage;

  if(int(max)>imageArrSize){
    for(unsigned i=0; i<unsigned(imageArrSize); i++){
      newimageArr[i] = imageArr[i];
      newxPosition[i] = xPosition[i];
      newyPosition[i] = yPosition[i];
    }

    for(unsigned i=imageArrSize; i<max; i++){
      newimageArr[i] = emptyImage;
    }
 }
  else{
    for(unsigned i=0; i<max; i++){
      newimageArr[i] = imageArr[i];
      newxPosition[i] = xPosition[i];
      newyPosition[i] = yPosition[i];
    }
  }

  _destroy();

  imageArrSize=max;
  imageArr= newimageArr;
  xPosition = newxPosition;
  yPosition = newyPosition;
}


//adds new sticker to stickersheet
int 	StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  int arrFull = 0;
  for(int i=0; i<imageArrSize; i++){
    if(imageArr[i].width()==0){
      imageArr[i]=sticker;
      xPosition[i]=x;
      yPosition[i]=y;
      break;
    }

    else if(i==imageArrSize-1){
      arrFull = -1;

    }
  }
  return arrFull;
}

//
bool 	StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if(imageArr[index].width()==0){
    return false;
  }
  else{
    xPosition[index] = x;
    yPosition[index] = y;
    return true;
  }
}

//removes sticker from stickersheet
void 	StickerSheet::removeSticker(unsigned index){
  Image emptyImage;
  imageArr[index]=emptyImage;

  xPosition[index]=0;
  yPosition[index]=0;
}

//gets sticker from array at a given index
Image *  StickerSheet::getSticker(unsigned index){
  if(imageArr[index].width()==0){
    return NULL;
  }
  Image * returnImagePtr;
  returnImagePtr = &imageArr[index];
  return returnImagePtr;
}


//creates an image with the basepicture overlayed with stickers or renders stickersheet
Image 	StickerSheet::render() const
  Image returnImage(basePicture);
  for(int i = 0; i < imageArrSize; i++){
    if((int(imageArr[i].width())+xPosition[i])>(int(returnImage.width()))){
      returnImage.resize(int(imageArr[i].width())+xPosition[i], basePicture.height());
    }
    if(int(imageArr[i].height())+yPosition[i]>(int(returnImage.height()))){
      returnImage.resize( basePicture.width(), int(imageArr[i].height())+yPosition[i]);
    }
  }

  for(int i = 0; i < imageArrSize; i++){
    for (int j = 0; j < int(imageArr[i].width()); j++) {
      for (int k = 0; k < int(imageArr[i].height()); k++) {
        HSLAPixel & pixel = returnImage.getPixel(j+xPosition[i], k+yPosition[i]);

        if((imageArr[i].getPixel(j,k)).a == 0){
          continue;
        }
        else if(imageArr[i].width()==0){
          continue;
        }
        else{
          pixel = imageArr[i].getPixel(j,k);
        }
      }
    }
  }

    return returnImage;
}
