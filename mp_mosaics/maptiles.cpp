/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    if(theTiles.empty() == true){
      return NULL;
    }
    //generate the canvas
    MosaicCanvas* mos = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
    //create the vector to store the points and a map 
    vector<Point<3>> theVector;
    map<Point<3>, int> tile;
    for(size_t i = 0; i < theTiles.size(); i++){
      //get the average color of the tile
      LUVAPixel pixel = theTiles[i].getAverageColor();
      
      //store the average color into the vector and store the i value in tile
      //to use later
      theVector.push_back(convertToXYZ(pixel));
      tile[theVector[i]] = i;
    }
    KDTree<3> theTree(theVector);
    for(int i = 0; i < theSource.getRows(); i++){
      for(int j = 0; j < theSource.getColumns(); j++){
        //Get the region color
        LUVAPixel pixel = theSource.getRegionColor(i,j);
        
        //get the point using findNN with our pixel
        Point<3> thePoint = theTree.findNearestNeighbor(convertToXYZ(pixel));
        
        //Use FNN and the corresponding position in theTile to generate the mosiac
        mos->setTile(i,j,&theTiles[tile[thePoint]]);
      }
    }
    return mos;
}

