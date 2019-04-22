/* Your code here! */
#include "dsets.h"

//creates num amount of unconnected nodes for the vector
void DisjointSets::addelements 	(int num){
	//Creates amount of unconnected nodes needed
	for(int i = 0; i < num; i++){
		DisjointSetsVector.push_back(-1);
	}
}
//compress the path and returns elem
int DisjointSets::find ( int  elem){
    //if we found our element, return it
    if((DisjointSetsVector[elem] < 0)){
        return elem;
    }
    else{
       //else recurse through vector to find require elem
       return DisjointSetsVector[elem] = find(DisjointSetsVector[elem]);
    }
}
//Joins together the 2 ints a and b
void DisjointSets::setunion ( int  a,int  b){
	// FIrst we need to find the pos of A and B
    int findA = find(a);
    int findB = find(b);
    
    //check for if they are the same and does nothing if they are
    if(findA == findB){
      return;
    }
    int setUnion = DisjointSetsVector[findA] + DisjointSetsVector[findB];
    //Then we need to check which one is bigger, if it is bigger
    if(DisjointSetsVector[findA] >= DisjointSetsVector[findB]){

    //Set that position equal to B
    DisjointSetsVector[findA] = findB;

    //Set B = A+B, union the 2
    ///DisjointSetsVector[findB] = DisjointSetsVector[findA] + //DisjointSetsVector[findB];
    DisjointSetsVector[findB] = setUnion;
    } else{

    //Set B = A
    DisjointSetsVector[findB] = findA;

    //Set A = A+B, union the 2
    DisjointSetsVector[findA] = setUnion;
    //DisjointSetsVector[findA] = DisjointSetsVector[findA] + //DisjointSetsVector[findB];
    }
}
//returns number of nodes in the up tree
int DisjointSets::size ( int  elem){
 // find size then times it by negative 1 to make it positive
 int get =  -1* DisjointSetsVector[find(elem)];
 return get;
}
