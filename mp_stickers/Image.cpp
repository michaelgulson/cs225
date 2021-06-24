#include "Image.h"
#include <cmath>
//Author: Michael Gulson
// Image is a subclass of PNG with more member functions for modifying the image


namespace cs225{

  //lightens image by adding .1 to luminance of each pixel
  void Image::lighten(){
    //private member variables must be accessed by using member functions
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if(pixelInput.l>.9){
          pixelInput.l=1.0;
        }
        else{
          pixelInput.l =  pixelInput.l + .1;
        }
      }
    }
  }

  //lightens image by adding amount to luminance of each pixel
  void 	Image::lighten (double amount){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.l+amount)>1.0){
          pixelInput.l=1.0;
        }
        else{
          pixelInput.l =  pixelInput.l + .1;
        }
      }
    }
  }

  //darkens image by subtracting .1 from luminance of each pixel
  void 	Image::darken (){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.l)<.1){
          pixelInput.l = 0;
        }
        else{
          pixelInput.l =  pixelInput.l - .1;
        }
      }
    }
  }

  //darkens image by subtracting amount from luminance of each pixel
  void 	Image::darken (double amount){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.l-amount)<0.0){
          pixelInput.l = 0.0;
        }
        else{
          pixelInput.l =  pixelInput.l - amount;
        }
      }
    }
  }

  //saturates image by adding .1 to saturation of each pixel
  void 	Image::saturate (){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if(pixelInput.s>.9){
          pixelInput.s=1.0;
        }
        else{
          pixelInput.s =  pixelInput.s + .1;
        }
      }
    }
  }

  //saturates image by adding amount to saturation of each pixel
  void 	Image::saturate (double amount){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.s+amount)>1.0){
          pixelInput.s=1.0;
        }
        else{
          pixelInput.s =  pixelInput.s + .1;
        }
      }
    }
  }

  //desaturates image by subtracting .1 from saturation of each pixel
  void 	Image::desaturate() {
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.s)<.1){
          pixelInput.s = 0;
        }
        else{
          pixelInput.s =  pixelInput.s - .1;
        }
      }
    }
  }

  //desaturates image by subtracting amount from saturation of each pixel
  void 	Image::desaturate (double amount){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        //check if l is greater than .9
        HSLAPixel & pixelInput = getPixel(i, j);
        if((pixelInput.s-amount)<0.0){
          pixelInput.s = 0.0;
        }
        else{
          pixelInput.s =  pixelInput.s - amount;
        }
      }
    }
  }

  //coverts image to grayscale by setting saturation of each pixel to 0
  void 	Image::grayscale (){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        HSLAPixel & pixel = getPixel(i, j);

        // `pixel` is a pointer to the memory stored inside of the PNG `image`,
        // which means you're changing the image directly.  No need to `set`
        // the pixel since you're directly changing the memory of the image.
        pixel.s = 0;
      }
    }

  }

  //rotates color of image by changing hue of each pixel
  void 	Image::rotateColor (double degrees){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        HSLAPixel & pixel = getPixel(i, j);
        if(pixel.h + degrees > 360){
          pixel.h = pixel.h + degrees-360;
        }
        else if(pixel.h + degrees < 0){
          pixel.h = pixel.h + degrees + 360;
        }
        else{
          pixel.h = pixel.h + degrees;

        }
      }
    }
  }

  //changes hue to orange and blue theme depending on the hue of each pixel
  void 	Image::illinify (){
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        HSLAPixel & pixel = getPixel(i, j);
        if(pixel.h<=113.5||pixel.h>=293.5){
          pixel.h=11.0;
        }
        else{
          pixel.h=216.0;
        }
      }
    }
  }

  //scales size of image by a factor
  void 	Image::scale (double factor){
    unsigned newHeight, newWidth;
    Image copyImage;
    copyImage.resize(width(),height());
    for (unsigned i = 0; i < width(); i++) {
      for (unsigned j = 0; j < height(); j++) {
        copyImage.getPixel(i,j) = getPixel(i, j);
      }
    }
    newWidth = int(width() * factor);
    newHeight = int(height() * factor);
    resize(newWidth, newHeight);
    for (unsigned i = 0; i < newWidth; i++) {
      for (unsigned j = 0; j < newHeight; j++) {
        getPixel(i,j) = copyImage.getPixel(int(i/factor),int(j/factor));

      }
    }
  }

  //scales width and height by separate factors
  void 	Image::scale (unsigned w, unsigned h){
    double ratioInit, ratioNew, factor;
    int newWidth, newHeight;
    ratioInit = double(width())/double(height());
    ratioNew = double(w)/double(h);
    if(ratioInit == ratioNew){
      Image::scale(ratioInit);
    }
    else if(ratioNew > ratioInit){
      //height stays constant
      newWidth = ratioInit*h;
      factor = double(newWidth)/double(width());
      Image::scale(factor);
    }
    else{
      //width stays constant
      newHeight = w/ratioInit;
      factor = double(newHeight)/double(height());
      Image::scale(factor);
    }
  }
}
