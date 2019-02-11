#include "StickerSheet.h"

///I initialized null stickers to have negative hues




namespace cs225{
void StickerSheet::_copy(StickerSheet const & other){
  // Clear self
  //delete[] imageArr;

  // Copy `other` to self
  imageArrSize = other.imageArrSize;
  //basePicture=*other.getBasePicture();
  for(unsigned j = 0; j < other.basePicture.width(); j++){
    for (unsigned k = 0; k < other.basePicture.height(); k++) {
      HSLAPixel & pixel =  basePicture.getPixel(j,k);
      pixel = other.basePicture.getPixel(j,k);
    }
  }
  imageArr = new Image[imageArrSize];
  xPosition = new int[imageArrSize];
  yPosition = new int[imageArrSize];
  for (int i = 0; i < imageArrSize; i++) {
    imageArr[i] = other.imageArr[i];
    xPosition[i] = xPosition[i];
    yPosition[i] = yPosition[i];
  }
}

void StickerSheet::_destroy(){
  delete [] imageArr;
  delete [] xPosition;
  delete [] yPosition;
}

StickerSheet::StickerSheet(const Image &picture, unsigned max){

/*
  imageArr= new Image[max];
  xPosition = new int[max];
  yPosition = new int[max];
  //basePicture = picture;
  for(unsigned j = 0; j < (*other.getBasePicture()).width(); j++){
    for (unsigned k = 0; k < (*other.getBasePicture()).height(); k++) {
      HSLAPixel & pixel =  basePicture.getPixel(j,k);
      pixel = (*other.getBasePicture()).getPixel(j,k);
    }
  }
  for(unsigned i=0; i<max; i++){
    HSLAPixel & firstPixel = imageArr[i].getPixel(0,0);;
    firstPixel.h = -1;    ///initialize NULL stickers to have negative hues
    firstPixel.s = 0;
    firstPixel.l = 1.0;
    firstPixel.a = 1.0;
    xPosition[i]=0;
    yPosition[i]=0;
  }
  imageArrSize = max;
  */
}
StickerSheet::~StickerSheet(){
  _destroy();
}
StickerSheet::StickerSheet(const StickerSheet &other){
  /*StickerSheet(*other.getBasePicture(), other.getimageArrSize());
  for(int i=0; i<imageArrSize; i++){
    addsticker(*other.getSticker(i), other.getxPosition(i), other.getyPosition(i));
  }*/
  //imageArr[0].getPixel(0,0) = NULL;
  _destroy();
  _copy(other);
}
const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
  /*getBasePicture
  getSticker (unsigned index)
  getimageArrSize()
  getxPosition(int index)
  getyPosition(int index)*/

  /*if (this != &other) {
    _destroy();
    _copy(other);
  }*/
  _destroy();
  _copy(other);
  return *this;
}
void 	StickerSheet::changeMaxStickers(unsigned max){
  Image * copyArr = new Image[imageArrSize];
  for(int i = 0; i<imageArrSize; i++){
    copyArr[i] = imageArr[i];
  }
  delete [] imageArr;
  imageArr = new Image[max];
  for(unsigned i = 0; i<max; i++){
      imageArr[i] = copyArr[i];
  }
}
int 	StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  int arrFull = 0;
  for(int i=0; i<imageArrSize; i++){
    HSLAPixel & firstPixel = imageArr[i].getPixel(0,0);

    /*h = 0;
    s = 0;
    l = 1.0;
    a = 1.0;
    */
    if(firstPixel.h<0)
      continue;
    else if(i==imageArrSize-1)
      arrFull = -1;
    else{
      //imageArr[i]=sticker
      for(unsigned j = 0; j < imageArr[i].width(); j++){
        for (unsigned k = 0; k < imageArr[i].height(); k++) {
          HSLAPixel & pixel =  imageArr[i].getPixel(j,k);
          pixel = sticker.getPixel(j,k);
        }
      }
      xPosition[i]=x;
      yPosition[i]=y;
    }
  }
  return arrFull;
}
bool 	StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  xPosition[index] = x;
  yPosition[index] = y;
  return true;
}
void 	StickerSheet::removeSticker(unsigned index){
  for(unsigned i = xPosition[index]; i < imageArr[index].width(); i++){
    for (unsigned j = yPosition[index]; j < imageArr[index].height(); j++) {

      HSLAPixel & pixel = imageArr[index].getPixel(i,j);;
      pixel = basePicture.getPixel(i,j);
    }
  }

  xPosition[index]=0;
  yPosition[index]=0;
}
/*Image &  StickerSheet::getBasePicture(){
  Image & returnImage = basePicture;
  return returnImage;
}*/
//making basePicture a public member f*** it
Image *  StickerSheet::getSticker(unsigned index){
  Image * returnImagePtr;
  returnImagePtr = &imageArr[index];
  return returnImagePtr;
}
Image 	StickerSheet::render() const{
  //return StickerSheet as an image
  Image returnImage(basePicture);
  for(int i = 0; i < imageArrSize; i++){
    for (int j = 0; j < int(returnImage.width()); j++) {
      for (int k = 0; k < int(returnImage.height()); k++) {
        HSLAPixel & pixel = returnImage.getPixel(j,k);
        //j is not within xPosition-imageArr[i].width()) continue
        /*if(j<xPosition[i]||j>xPosition[i]+int(imageArr[i].width()))
          continue;
        //k is within yPosition-imageArr[i].height()
        else if(k<yPosition[i]||k>yPosition[i]+int(imageArr[i].height()))
          continue;
        //i is within xPosition-imageArr[j].width())
        //j is within yPosition-imageArr[k].height()
        else if(pixel.a==0.0)
          continue;
        else if(pixel.h<0)////NULL image
          continue;
        else*/
          pixel = imageArr[i].getPixel(j,k);
      }
    }
  }
  return returnImage;
}
} //namespace cs225{}
/*bool StickerSheet::operator!= (StickerSheet const & other) const {
  return !(*this == other);
}

bool PNG::operator== (PNG const & other) const {
  if (width_ != other.width_) { return false; }
  if (height_ != other.height_) { return false; }

  for (unsigned i = 0; i < width_ * height_; i++) {
    HSLAPixel & p1 = imageData_[i];
    HSLAPixel & p2 = other.imageData_[i];
    if (p1 != p2) { return false; }
  }
*/

/*int StickerSheet::getimageArrSize(){
  return imageArrSize;
}*/
/*void StickerSheet::setimageArrSize(int size){
  imageArrSize = size;
}*/
/*
int StickerSheet::getxPosition(int index){
  return xPosition[index];
}
int StickerSheet::getyPosition(int index){
  return yPosition[index];
*/
