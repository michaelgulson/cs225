#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  
  //ImageTraversal::Iterator Iter = new ImageTraversal::Iterator()
  //Iter = begin();
  //impliment in iterator unnecessary to do here
  /*available indicates not in stack and 
  if right pixel(x+1) available: add
  else if below pixel(y+1) available: add
  else if left pixel(x-1) available: add
  else    above pixel(y-1) available: add
  */
  //while(Iter!= begin()){
  //  Iter++;
  //  add(Iter.point);
  //}

  _stack.push(start);
  //_end = NULL;
  _png = png;
  _start = start;
  _tolerance = tolerance;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  DFS *imgTraversal = new DFS(_png, _start, _tolerance);
  return ImageTraversal::Iterator(_png, _start, _tolerance, imgTraversal);
  // return ImageTraversal::Iterator(_start);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  _stack.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point pt = _stack.top();
  _stack.pop();
  return pt;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  Point pt = _stack.top();
  return pt;
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return _stack.empty();
}