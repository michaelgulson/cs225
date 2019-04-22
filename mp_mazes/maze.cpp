/* Your code here! */
//Do nothing
#include "maze.h"
SquareMaze::SquareMaze()
{
}

//Clear all entries in vectors
void SquareMaze::clearTheMaze()
{

  for (int i = 0; i < mazeSize; i++)
  {
  }
  int temp1 = xPos.size();
  for (int i = 0; i < temp1; i++)
  {
    xPos.pop_back();
  }
  int temp2 = yPos.size();
  for (int i = 0; i < temp2; i++)
  {
    yPos.pop_back();
  }
  int temp3 = direction.size();
  for (int i = 0; i < temp3; i++)
  {
    direction.pop_back();
  }
  int temp4 = doesExist.size();
  for (int i = 0; i < temp4; i++)
  {
    doesExist.pop_back();
  }
  int temp5 = downWallExist.size();
  for (int i = 0; i < temp5; i++)
  {
    downWallExist.pop_back();
  }
  int temp6 = rightWallExist.size();
  for (int i = 0; i < temp6; i++)
  {
    rightWallExist.pop_back();
  }

  //Sets all variables to zero
  mazeWidth = 0;
  mazeHeight = 0;
  mazeSize = 0;
}

//Method to create all the walls
void SquareMaze::createWalls()
{
  //Use this method to create walls, in case I need to create them again in the future.
  for (int i = 0; i < mazeSize; i++)
  {
    downWallExist.push_back(true);
  }

  //Have these seperated as to if they need to be different it makes it easier.
  for (int i = 0; i < mazeSize; i++)
  {
    rightWallExist.push_back(true);
  }
}

//Makes a new maze using the paramters od width and height to create the maze
void SquareMaze::makeMaze(int width, int height)
{
  //FIrst we need to clear all existing data
  clearTheMaze();

  //Set variables
  mazeWidth = width;
  mazeHeight = height;
  mazeSize = width * height;

  //FIll the maze with walls at all points
  createWalls();

  //Create a new disjointSet and add the element size
  DisjointSets theSets;
  theSets.addelements(mazeSize);
  int i = 0;
  //srand(time(NULL));
  while (i < mazeSize - 1)
  {

    //Get random x and y values
    int posX = rand() % mazeWidth;
    int posY = rand() % mazeHeight;

    //Get values needed to test whether to destory a wall or not
    int hold = (posY * mazeWidth) + posX;
    int holdDown = posX + (posY + 1) * mazeWidth;

    //logic behind deleting walls to form the maze
    if (posX < (mazeWidth - 1) && rightWallExist[hold] == true && theSets.find(hold) != theSets.find(hold + 1))
    {
      rightWallExist[hold] = false;
      theSets.setunion(theSets.find(hold), theSets.find(hold + 1));
      i++;
    }
    else if (posY < (mazeHeight - 1) && downWallExist[hold] == true && theSets.find(hold) != theSets.find(holdDown))
    {
      downWallExist[hold] = false;
      theSets.setunion(theSets.find(hold), theSets.find(holdDown));
      i++;
    }
  }
}

//Method that determins if a player can travel a certain direct, ie is their no wall
bool SquareMaze::canTravel(int x, int y, int dir) const
{
  if (dir < 4 && dir > -1)
  {
    int xPosition = (y * mazeWidth) + x;

    //CHeck for rightwall
    if (dir == 0)
    {
      if (rightWallExist[xPosition] == true)
      {
        return false;
      }
      else
      {
        return true;
      }
      //CHeck for up wall
    }
    else if (dir == 1)
    {
      if (downWallExist[xPosition] == true)
      {
        return false;
      }
      else
      {
        return true;
      }
      //check fo left wall
    }
    else if (dir == 2)
    { //x==0 x > mazeHeight
      if (x == 0)
      {
        return false;
      }
      if (rightWallExist[xPosition - 1] == true || x <= 0 || x > mazeWidth)
      {
        return false;
      }
      else
      {
        return true;
      }
      //check for down wall
    }
    else if (dir == 3)
    {
      if (y == 0)
      {
        return false;
      }
      if (downWallExist[mazeWidth * (y - 1) + x] == true || y <= 0 || y > mazeHeight)
      {
        return false;
      }
      else
      {
        return true;
      }
    }
    //If not anything above return false
  }
  else
  {
    return false;
  }
  return false;
}

//Sets if a wall is their or not, use to manually create maze
void SquareMaze::setWall(int x, int y, int dire, bool exists)
{
  int xPosition = mazeWidth * y + x;
  if (dire == 0 || dire == 1)
  {
    if (dire == 0)
    {
      rightWallExist[xPosition] = exists;
    }
    else
    {
      downWallExist[xPosition] = exists;
    }
  }
}

//Deletes perivous solution every time the player wants to draw the current solution
void SquareMaze::clearThePath()
{
  int temp = holdQ.size();
  for (int i = 0; i < temp; i++)
  {
    holdQ.pop();
  }
  holdQ.push(0);
  int temp2 = getTheRows.size();
  for (int i = 0; i < temp2; i++)
  {
    getTheRows.pop_back();
  }
  int temp3 = getPath.size();
  //for(int i = 0; i< temp3; i++){
  getPath.clear();
  //}
  int temp4 = alreadyVisit.size();
  for (int i = 0; i < temp4; i++)
  {
    alreadyVisit.pop_back();
  }
  int temp5 = mazeWidth * mazeHeight;

  //Sets up to create the solution
  for (int i = 0; i < temp5; i++)
  {
    alreadyVisit.push_back(false);
  }
  alreadyVisit[0] = true;
}

//Checks if player is able to go a certain direction
bool SquareMaze::canGoDirct(int dire, int visit)
{
  //std:: cout << "hello 7" << std::endl;

  //if they can and they haven't alrady then they are allowed to go that direct
  if (canTravel(getX, getY, dire) == true && alreadyVisit[visit] == false)
  {
    //std:: cout << "hello 8" << std::endl;
    return true;
  }
  return false;
}

//Code to insert the direction the player went to
void SquareMaze::goDirct(int dire, int visit)
{
  getPath.insert(std::pair<int, int>(dire, visit));
  alreadyVisit[dire] = true;
  holdQ.push(dire);
}

//SOlves the maze
std::vector<int> SquareMaze::solveMaze()
{
  //std:: cout << "hello 2" << std::endl;

  //Delte pervious solution
  clearThePath();

  //While we haven't reached the end
  while (holdQ.empty() == false)
  {

    //Go in a direct
    int frontQ = holdQ.front();
    holdQ.pop();
    getX = frontQ % mazeWidth;
    getY = frontQ / mazeWidth;
    //std:: cout << "hello 3" << std::endl;

    //Keep going
    if (getY == mazeHeight - 1)
    {
      getTheRows.push_back(frontQ);
    }
    //std:: cout << "hello 5" << std::endl;

    //CHecks to see if you can go in a direct
    if (canGoDirct(0, frontQ + 1) == true)
    {
      goDirct(frontQ + 1, frontQ);
    }
    if (canGoDirct(1, frontQ + mazeWidth) == true)
    {
      goDirct(frontQ + mazeWidth, frontQ);
    }
    if (canGoDirct(2, frontQ - 1) == true)
    {
      goDirct(frontQ - 1, frontQ);
    }
    if (canGoDirct(3, frontQ - mazeWidth) == true)
    {
      goDirct(frontQ - mazeWidth, frontQ);
    }
    //std:: cout << "hello 4" << std::endl;
  }
  //std:: cout << "hello 1" << std::endl;

  //Transforms the directions into a vector of 0,1,2,3 that reprsents direction
  std::vector<int> returnVect;
  int getLast = getTheLast();
  int begining = getTheRows[getLast];
  while (begining != 0)
  {
    int i = getPath[begining];
    if (begining == i + 1)
    {
      returnVect.push_back(0);
    }
    else if (begining == i + mazeWidth)
    {
      returnVect.push_back(1);
    }
    else if (begining == i - 1)
    {
      returnVect.push_back(2);
    }
    else if (begining == i - mazeWidth)
    {
      returnVect.push_back(3);
    }
    begining = i;
  }
  reverse(returnVect.begin(), returnVect.end());
  return returnVect;
}

//Helper meathod to set up an unslve maze
cs225::PNG *SquareMaze::setUpMaze(int start, int end, int zero, cs225::PNG *&theMaze)
{
  cs225::HSLAPixel *getPix;
  for (int i = start; i < end; i++)
  {
    if (zero == 0)
    {
      getPix = &theMaze->getPixel(0, i);
    }
    else
    {
      getPix = &theMaze->getPixel(i, 0);
    }
    getPix->l = 0.0;
  }
  return theMaze;
}

//Helper meathod to set up an unslve maze
cs225::PNG *SquareMaze::setUpMaze2(int start, int end, int which, int left, int right, cs225::PNG *&theMaze)
{
  cs225::HSLAPixel *getPix;
  for (int i = start; i < end; i++)
  {
    if (which == 0)
    {
      getPix = &theMaze->getPixel(left, right + i);
    }
    else
    {
      getPix = &theMaze->getPixel(left + i, right);
    }

    getPix->l = 0.0;
  }
  return theMaze;
}
//Get the last
int SquareMaze::getTheLast()
{
  int getLast = mazeWidth - 1;
  while (getTheRows[getLast] == getTheRows[getLast - 1])
  {
    getLast = getLast - 1;
  }
  return getLast;
}

//Draws an unsolved maze
cs225::PNG *SquareMaze::drawMaze()
{

  //Creates blank canvas
  int drawHeight = (mazeHeight * 10) + 1;
  int drawWidth = (mazeWidth * 10) + 1;
  cs225::PNG *theMaze = new cs225::PNG(drawWidth, drawHeight);

  //Sets up mazes edge
  theMaze = setUpMaze(0, drawHeight, 0, theMaze);
  theMaze = setUpMaze(10, drawWidth, 1, theMaze);

  //Sets up mazes walls
  for (int i = 0; i < mazeWidth; i++)
  {
    for (int j = 0; j < mazeHeight; j++)
    {
      if (rightWallExist[(mazeWidth * j) + i] == true)
      {
        theMaze = setUpMaze2(0, 11, 0, (i + 1) * 10, (10 * j), theMaze);
      }
      if (downWallExist[(mazeWidth * j) + i] == true)
      {
        theMaze = setUpMaze2(0, 11, 1, (10 * i), (j + 1) * 10, theMaze);
      }
    }
  }
  return theMaze;
}

//Helper method to draw a solved maze
cs225::PNG *SquareMaze::solveMaze2(int &startX, int &startY, int which, cs225::PNG *&theMaze)
{
  for (int i = 0; i < 10; i++)
  {
    cs225::HSLAPixel *getPix = &theMaze->getPixel(startX, startY);
    getPix->l = 0.5;
    getPix->h = 0;
    getPix->s = 1;
    if (which == 0)
    {
      startX = startX + 1;
    }
    else if (which == 1)
    {
      startY = startY + 1;
    }
    else if (which == 2)
    {
      startX = startX - 1;
    }
    else if (which == 3)
    {
      startY = startY - 1;
    }
  }
  return theMaze;
}

//Draws maze with solution
cs225::PNG *SquareMaze::drawMazeWithSolution()
{

  //Sets up unsolved maze
  cs225::PNG *theMaze = drawMaze();
  std::vector<int> getDirections = solveMaze();

  //told to start here
  int startX = 5;
  int startY = 5;

  //Draws the path using the solution vector
  for (unsigned i = 0; i < getDirections.size(); i++)
  {
    theMaze = solveMaze2(startX, startY, getDirections[i], theMaze);
  }

  //Sets up ending
  cs225::HSLAPixel *getPix = &theMaze->getPixel(startX, startY);
  getPix->l = 0.5;
  getPix->h = 0;
  getPix->s = 1;
  getPix->a = 1;
  startX = startX - 4;
  startY = startY + 5;
  for (int i = 0; i < 9; i++)
  {
    cs225::HSLAPixel *getPix = &theMaze->getPixel(startX, startY);
    getPix->l = 1;
    getPix->a = 1;
    startX = startX + 1;
  }
  return theMaze;
}

//FOR CREATIVE PART: PART 3

//Helper meathod to set up an unslve maze
cs225::PNG *SquareMaze::setUpCreativeMaze(int start, int end, int zero, cs225::PNG *&theMaze)
{
  cs225::HSLAPixel *getPix;
  for (int i = start; i < end; i++)
  {
    if (zero == 0)
    {
      getPix = &theMaze->getPixel(0, i);
    }
    else
    {
      getPix = &theMaze->getPixel(i, 0);
    }
    getPix->l = 0.0;
  }
  return theMaze;
}

//Helper meathod to set up an unslve maze
cs225::PNG *SquareMaze::setUpCreativeMaze2(int start, int end, int which, int left, int right, cs225::PNG *&theMaze)
{
  cs225::HSLAPixel *getPix;
  for (int i = start; i < end; i++)
  {
    if (which == 0)
    {
      getPix = &theMaze->getPixel(left, right + i);
    }
    else
    {
      getPix = &theMaze->getPixel(left + i, right);
    }

    getPix->l = 0.0;
  }
  return theMaze;
}
//Get the last
int SquareMaze::getTheLastCreative()
{
  int getLast = mazeWidth - 1;
  while (getTheRows[getLast] == getTheRows[getLast - 1])
  {
    getLast = getLast - 1;
  }
  return getLast;
}

//Draws an unsolved maze
cs225::PNG *SquareMaze::drawCreativeMaze()
{

  //Creates blank canvas
  int drawHeight = (mazeHeight * 10) + 1;
  int drawWidth = (mazeWidth * 10) + 1;
  cs225::PNG *theMaze = new cs225::PNG(drawWidth, drawHeight);

  //Sets up mazes edge
  theMaze = setUpCreativeMaze(0, drawHeight, 0, theMaze);
  theMaze = setUpCreativeMaze(10, drawWidth, 1, theMaze);

  //Sets up mazes walls
  for (int i = 0; i < mazeWidth - 40; i++)
  {
    for (int j = 0; j < mazeHeight - 20; j++)
    {
      if (rightWallExist[(mazeWidth * j) + i] == true || i == (mazeWidth - 40) - 1)
      {
        theMaze = setUpCreativeMaze2(0, 11, 0, (i + 1) * 10, (10 * j), theMaze);
      }
      if (downWallExist[(mazeWidth * j) + i] == true || j == 0)
      {
        theMaze = setUpCreativeMaze2(0, 11, 1, (10 * i), (j + 1) * 10, theMaze);
      }
    }
  }
  for (int i = 0; i < mazeWidth; i++)
  {
    for (int j = mazeHeight - 20; j < mazeHeight; j++)
    {
      if (rightWallExist[(mazeWidth * j) + i] == true || i == (mazeWidth - 1))
      {
        theMaze = setUpCreativeMaze2(0, 11, 0, (i + 1) * 10, (10 * j), theMaze);
      }
      if (downWallExist[(mazeWidth * j) + i] == true || (j == mazeHeight - 20 && i > mazeWidth - 40) || j == mazeHeight - 1)
      {
        theMaze = setUpCreativeMaze2(0, 11, 1, (10 * i), (j + 1) * 10, theMaze);
      }
    }
  }
  return theMaze;
}
