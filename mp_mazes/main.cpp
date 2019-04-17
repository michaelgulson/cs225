#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;


int main()
{
    // Write your own main here
    //cout << "Add your own tests here! Modify main.cpp" << endl;
   SquareMaze maz;
  maz.makeMaze(60,60);
  cs225::PNG* maze = maz.drawCreativeMaze();
  maze->writeToFile("creative.png");
    return 0;
}
