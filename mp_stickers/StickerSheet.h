/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

namespace cs225{
  class StickerSheet{

    public:
      StickerSheet(const Image &picture, unsigned max);
      ~StickerSheet();
      StickerSheet(StickerSheet const &other);
      const StickerSheet & 	operator=(const StickerSheet &other);
      void 	changeMaxStickers(unsigned max);
      int 	addSticker(Image &sticker, unsigned x, unsigned y);
      bool 	translate(unsigned index, unsigned x, unsigned y);
      void 	removeSticker(unsigned index);
      Image *	getSticker(unsigned index);
      Image 	render() const;
      //int getimageArrSize() const;
      //int getxPosition(int index) const;
      //int getyPosition(int index) const;


      Image basePicture;
      Image * imageArr;
      int imageArrSize;
      int * xPosition;//position on base image array
      int * yPosition;

    private:



      void _copy(StickerSheet const & other);
      void _destroy();
 };


}
