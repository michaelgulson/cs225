#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>


/////////////USE ADJLIST algotithm in slides////////////

//"MP tests are designed to ensure you have an implementation that"
//"runs in the running time described in lecture of the adjacency list"
// with the exception of vertex/edge removal


/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::numVertices() const {
  //use adjacency matrix
  // TODO: Part 2
  return vertexMap.size();
}


/**
* The degree of the vertex. For directed: Sum of in-degree and out-degree
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  //iterate through edges
  //find the number of edges with v as source_ or dest_

  //brute force algorithm///////////////////////
  // unsigned int degreeNum = 0;
  // edgeListIter it = edgeList.begin();
  // for (it = edgeList.begin(); it != edgeList.end(); it++){
  //   if(it->dest_ == v|| it->source_  == v){
  //     degreeNum++;
  //   }
  // }
  // return degreeNum;
  ///////////////////////////////////
  ///psuedocode
  unsigned int degreeNum = 0;
  char * Key = v->key;
  auto edgeList= adjList.find(Key);
  return edgeList.size();

}


/**
* Inserts a Vertex into the Graph.
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  std::pair<std::string, V_byRef> insertV(key, v);


  //???when we insert a vertex do we not create edges? 0 egdges in adjList

  //insert into vertex map
  vertexMap.insert(insertV);

  //initialize entry into adjList empty list
  std::list<edgeListIter> emptyList;
  adjList.push_back(emptyList);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  //THIS FUNCTION CAN BE BRUTE FORCED(efficiency isn't important)

  auto vertIt = vertexMap.find(key);
  //remove vertex from map
  vertexMap.erase(key);

  //remove all edges with v from edgeListIter

  auto it = edgeList.begin();
  for (it = edgeList.begin(); it != edgeList.end(); it++){
    if (it->dest_ == (*vertIt) || it->source_ == (*vertIt))
    {
      edgeList.erase(key);
    }
  }

  //erase from ADJLIST
  adjList.erase(key);

  return;

}


/**
* Inserts an Edge into the Graph.
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2

  //insert edge into edgeList
  E & e = *(new E(v1, v2));
  edgeList.insert(e);


  //insert edge into adjList
  ////IS v1->key correct??///////
  auto edgeIter = edgeList.find(e);


  auto v1adjList = adjList.find(v1->key);
  v1adjList.push_back(edgeIter);

  auto v2adjList = adjList.find(v2->key);
  v2adjList.push_back;

  return e;
}


/**
* Removes an Edge from the Graph. Consider both the undirected and directed cases.
* min(degree(key1), degree(key2))
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2

  //THIS FUNCTION CAN BE BRUTE FORCED(efficiency isn't important)

  //V V1, V2;
  auto V1iter = vertexMap.find(key1);
  auto V2iter = vertexMap.find(key2);
  
  auto deleteEdge = edgeList.begin();

  auto it = edgeList.begin();
  for (it = edgeList.begin(); it != edgeList.end(); it++){
    if (((it->dest_ == (*V1iter)) && (it->source_ == (*V2iter))) || ((it->dest_ == (*V2iter)) && (it->source_ == (*V1iter))))
    {
      deleteEdge = it;
      edgeList.erase(it);
    }
  }

  //remove vertexes from adjList
  auto v1adjList = adjList.find(key1);
  auto v2adjList = adjList.find(key2);
  
  //delete v2 from v1 adjacency list
  auto deleteItr = v1adjList.find((*V2iter));
  v1adjList.remove(deleteItr);

  //delete v1 from v2 adjacency list
  deleteItr = v2adjList.find((*V1iter));
  v2adjList.remove(deleteItr);
  return;
}


/**
* Removes an Edge from the Graph given by the location of the given iterator into the edge list.
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2

 

   //remove vertexes from adjList
  auto v1adjList = adjList.find(it->dest_->key);
  auto v2adjList = adjList.find(it->source_->key);

  //delete v2 from v1 adjacency list
  auto deleteItr = v1adjList.find(it->source_->key);
  v1adjList.remove(deleteItr);

  //delete v1 from v2 adjacency list
  deleteItr = v2adjList.find(it->dest_->key);
  v2adjList.remove(deleteItr);
  

  //remove edge from edgeList
  edgeList.erase(it);


  return;
}


/**
* Return the list of incident edges from a given vertex.
* For the directed case, consider all edges that has the vertex as either a source or destination.
* @param key The key of the given vertex
* @return The list edges (by reference) that are adjacent to the given vertex
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another. Consider both the undirected and directed cases.
* When the graph is directed, v1 and v2 are only adjacent if there is an edge from v1 to v2.
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  return false;
}
