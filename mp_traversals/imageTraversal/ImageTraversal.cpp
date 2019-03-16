#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

bool ImageTraversal::Iterator::hasVisited(int x, int y)
{
  for ( int i = 0; i < _visitedXYCount; i++)
  {

      if(_visitedX[i]==x&&_visitedY[i]==y){
        return true;
      }

  }
  return false;
}

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(){
    /** @todo [Part 1] */

    /*As part of “visiting” a point, a traversal must add all of the neighbors that will be visited at some time in the future. Every point has up to four neighbors (and the neighbors MUST be added in the following order):

      The pixel to the right, (x + 1),
      The pixel below, (y + 1), and
      The pixel to the left, (x - 1).
      The pixel above, (y - 1),
*/
    _traversal = NULL;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal *traversal)
{
  /** @todo [Part 1] */

  /*As part of “visiting” a point, a traversal must add all of the neighbors that will be visited at some time in the future. Every point has up to four neighbors (and the neighbors MUST be added in the following order):

      The pixel to the right, (x + 1),
      The pixel below, (y + 1), and
      The pixel to the left, (x - 1).
      The pixel above, (y - 1),
*/
_png = png;
_start = start;
_tolerance = tolerance;
_curr = start;
_traversal = traversal;
_traversal->add(start);
//_end = end;
//_isAtEnd = FALSE;
_visitedX = new int[_png.width()*_png.height()];     //fix this
_visitedY = new int[_png.width() * _png.height()];   //fix this
_visitedXYCount = 0;
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //Iter = begin();
  //impliment in iterator unnecessary to do here
  /*available indicates not in stack and 
  if right pixel(x+1) available: add
  else if below pixel(y+1) available: add
  else if left pixel(x-1) available: add
  else    above pixel(y-1) available: add
  */
  //Point next;
  if(_traversal->empty()){
    _traversal = NULL;
    return *(this);
  }
  _curr = _traversal->pop(); //ta said I should pop
  if ((unsigned)_visitedXYCount < (_png.width() * _png.height())-1){  
    _visitedX[_visitedXYCount] = (_curr.x);
    _visitedY[_visitedXYCount] = (_curr.y);
  }
  _visitedXYCount++;
  //check right, traverse right
  //check if already visited
  if (((_curr.x) != _png.width() - 1) && !hasVisited(_curr.x + 1, _curr.y))
  {
    _traversal->add(Point(_curr.x + 1, _curr.y));
  }
  //check below, traverse below
  if(((_curr.y)!=_png.height()-1)&&!hasVisited(_curr.x,_curr.y+1)){
    //_curr = Point(_curr.x,_curr.y+1);
    //pop();
    _traversal->add(Point(_curr.x, _curr.y + 1));
  }
  //check left, traverse left
  if(((_curr.x)!=0)&&(!hasVisited(_curr.x-1,_curr.y))){
    //_curr = Point(_curr.x-1, _curr.y);
    //pop();
    _traversal->add(Point(_curr.x - 1, _curr.y));
  }
  //check above traverse above
  if (((_curr.y) != 0) && !hasVisited(_curr.x, _curr.y-1))
  {
    //_curr = Point(_curr.x, _curr.y-1);
    //pop();
    _traversal->add(Point(_curr.x, _curr.y - 1));
  }
  return *(this);
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return _curr;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  if (_traversal == NULL && other._traversal == NULL)
  {
    return false;
  }
  else if (_traversal == NULL && other._traversal != NULL)
  {
    return true;
  }
  else if (_traversal != NULL && other._traversal == NULL)
  {
    return true;
  }
  else{
    if (_traversal == other._traversal)
    {
      return false;
    }
    else{
      return true;
    }
  }
}
