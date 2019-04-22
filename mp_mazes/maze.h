/* Your code here! */
//#ifndef _DSETS_
//#define _DSETS_
#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "cs225/PNG.h"
#include "dsets.h"

class SquareMaze
{

public:
  //required functions
  SquareMaze();
  void makeMaze(int width, int height);
  bool canTravel(int x, int y, int dir) const;
  void setWall(int x, int y, int dire, bool exists);
  std::vector<int> solveMaze();
  cs225::PNG *drawMaze();
  cs225::PNG *drawMazeWithSolution();
  void clearTheMaze();
  void clearThePath();

  //int find 	( 	int  	elem	) 	;
  //void setunion 	( 	int  	a,
  //                  int  	b
  //) ;
  //int size 	( 	int  	elem	) 	;
  cs225::PNG *drawCreativeMaze();

private:
  //THINGS I MAY NEED AS I READ IT
  void createWalls();
  int mazeWidth;
  int mazeHeight;
  int mazeSize;
  int getX = 0;
  int getY = 0;

  std::vector<int> xPos;
  std::vector<int> yPos;
  std::vector<int> direction;
  std::vector<bool> doesExist;
  std::vector<bool> downWallExist;
  std::vector<bool> rightWallExist;
  cs225::PNG *setUpMaze(int start, int end, int zero, cs225::PNG *&theMaze);
  cs225::PNG *setUpMaze2(int start, int end, int which, int left, int right, cs225::PNG *&theMaze);
  cs225::PNG *solveMaze2(int &startX, int &startY, int which, cs225::PNG *&theMaze);

  cs225::PNG *setUpCreativeMaze(int start, int end, int zero, cs225::PNG *&theMaze);
  cs225::PNG *setUpCreativeMaze2(int start, int end, int which, int left, int right, cs225::PNG *&theMaze);
  int getTheLastCreative();

  bool canGoDirct(int dire, int visit);
  void goDirct(int dire, int visit);
  int getTheLast();
  std::queue<int> holdQ;
  std::vector<int> getTheRows;
  std::map<int, int> getPath;
  std::vector<bool> alreadyVisit;

  //Required datastruct
  std::vector<bool> DisjointSetsVector;
};
#endif