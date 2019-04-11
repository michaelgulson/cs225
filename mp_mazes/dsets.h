/* Your code here! */
#ifndef _DSETS_
#define _DSETS_
#include <algorithm>
#include <vector>

class DisjointSets
{

  public:
    //required functions
    void addelements(int num);
    int find(int elem);
    void setunion(int a,
                  int b);
    int size(int elem);

  private:
    //Required datastruct
    std::vector<int> DisjointSetsVector;
};
#endif