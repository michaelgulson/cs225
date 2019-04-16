/* Your code here! */
#ifndef _DSETS_
#define _DSETS_
#include <algorithm>
#include <vector>

<<<<<<< HEAD
class DisjointSets{

public:
//required functions
void addelements 	( 	int  	num	) 	;
int find 	( 	int  	elem	) 	;
void setunion 	( 	int  	a,
                                int  	b
) ;
int size 	( 	int  	elem	) 	;

private:
//Required datastruct
std::vector<int> DisjointSetsVector;
};
#endif
=======
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
>>>>>>> dbdc6680de42d6c082c19a48306bfde0a55ab95c
