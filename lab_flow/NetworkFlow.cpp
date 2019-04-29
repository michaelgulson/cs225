/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

//Methof for inserting flow, need to set edge and weight
void NetworkFlow::insertingFlowEdges(Edge theEdge){
  flow_.insertEdge(theEdge.source,theEdge.dest);
  flow_.setEdgeWeight(theEdge.source,theEdge.dest,0);
}

//Same thing as above, just with residual.
void NetworkFlow::insertingResidualEdges(Edge theEdge,int whichWay){
  if(whichWay == 0){
    residual_.insertEdge(theEdge.source,theEdge.dest);
    residual_.setEdgeWeight(theEdge.source,theEdge.dest,theEdge.getWeight());
  } else if(whichWay == 1){
    residual_.insertEdge(theEdge.dest,theEdge.source);
    residual_.setEdgeWeight(theEdge.dest,theEdge.source,0);
  }
}
NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  // YOUR CODE HERE
  //FIrst we need to get a vector of thr vertices in order to set the graph
  vector<Vertex> getVerti = g_.getVertices();
  
  //Set the flow to be 0 as we haven't done anything yet
  maxFlow_ = 0;
  
  //Now we need to set the flow and residual, using the verteices we have
  //SImply insert them into the residual and flow
  for(size_t i = 0; i < getVerti.size(); i++){
    residual_.insertVertex(getVerti[i]);
    flow_.insertVertex(getVerti[i]);
  }
  
  //Now that we have flow and residual set, we can now get the edges of the graph
  //Using the edgeds we obtain we can now set the flow and residuals
  vector<Edge> getTheEdges = g_.getEdges();
  for(size_t i = 0; i < getTheEdges.size(); i++){
    //Set the flow
    insertingFlowEdges(getTheEdges[i]);
    
    //Need to set the residual both ways
    insertingResidualEdges(getTheEdges[i],0);
    insertingResidualEdges(getTheEdges[i],1);
  }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */
//Method to finding the pathCapa
int NetworkFlow::FindMinPath(const std::vector<Vertex> & path,int findMinWeight) const{
  //Go through the path
  for(size_t i = 0; i < path.size() - 1; i++){
    //Geth the edge of the residual
    Edge theEdge = residual_.getEdge(path[i], path[i+1]);
    
    //If the edge wieght is less then THE minimum we had, then set that
    //as new minimum
    if(theEdge.getWeight() < findMinWeight){
      findMinWeight = theEdge.getWeight();
    }
  }
  return findMinWeight;
}
int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  //Obtain the edge
  Edge theEdge = residual_.getEdge(path[0],path[1]);
  
  //Using the First width, find the minimum Weight and that is the pathCapa
  int findMinWeight = FindMinPath(path,theEdge.getWeight());
  return findMinWeight;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */
  //Method for setting flow, nothing special just use same code as last
  //Lab basically
void NetworkFlow::settingTheFlow(Vertex one, Vertex two, int pathCapaci){
  Edge theEDge = flow_.getEdge(one,two);
  flow_.setEdgeWeight(one,two,theEDge.getWeight() + pathCapaci);
}

//Method for setting residual, nothing special just use same code as last
//Lab basically
void NetworkFlow::settingTheResidual(Vertex one, Vertex two, int pathCapaci){
  Edge theEDge = residual_.getEdge(one,two);
  residual_.setEdgeWeight(one,two,theEDge.getWeight() + pathCapaci);
}
const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
  //Get the path of verteices
  vector<Vertex> getTheVert;
  
  //WHile the path is true then we can contiune through it
  while(findAugmentingPath(source_,sink_,getTheVert) == true){
    //First get The pathCapa and store it
    int getPathCapacity = pathCapacity(getTheVert);
    
    //The sum of all the pathCapa is the max flow, so contiunally add
    //it to the flow
    maxFlow_ = maxFlow_ + getPathCapacity;
    
    //GO through the path
    for(size_t i = 0; i < getTheVert.size() - 1; i++){
      
      //If the flow exist then we can set the flow as normal
      if(flow_.edgeExists(getTheVert[i],getTheVert[i+1]) == true){
        settingTheFlow(getTheVert[i],getTheVert[i+1],getPathCapacity);
      } else{
        //If not we have to reverse it
        settingTheFlow(getTheVert[i+1],getTheVert[i],(-getPathCapacity));
      }
      
      //Set the risdual, need to do this both ways.
      settingTheResidual(getTheVert[i+1],getTheVert[i],(getPathCapacity));
      settingTheResidual(getTheVert[i],getTheVert[i+1],(-getPathCapacity));
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

