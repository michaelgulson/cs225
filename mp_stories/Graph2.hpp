#include <queue>
#include <algorithm>
#include <string>
#include <list>

/**
 * Returns an std::list of vertex keys that creates any shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * You should use undirected edges. Hint: There are no edge weights in the Graph.
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  // TODO: Part 3
  //Create the needed list for the code
  std::list<std::string> path;
  std::queue<string>theQueue;
  std::unordered_map<string,string> thePredator;
  
  //Create these variables so I don't have to rewrite them
  auto begining = vertexMap.begin();
  auto ending = vertexMap.end();
  
  //GO through the iterator and create a path of empty spots
  for(auto it = begining; it != ending; it++){
    auto key = it->first;
    thePredator[key] = "our empty soul";
  }
  
  //STart the queue and path
  theQueue.push(start);
  thePredator[start] = "start";
  
  //WHile we still haven't reached the end
  while(theQueue.empty() == false){
    
    //Get the firt spot then delete it
    string frontQueue = theQueue.front();
    theQueue.pop();
    
    //Iterate through vertex and at every spot
    for(auto it = begining; it != ending; it++){
      
      //Create a key to hold the key we have
      auto key = it->first;
      
      //GO through everyspot of the adjLIst at queue
      for(auto edgeIter: adjList.at(frontQueue)){
        
        //CHeck to see if either of the keys are what is in it
        auto getKey1 = (*edgeIter).get().source().key();
        auto getKey2 = (*edgeIter).get().dest().key();
        if(getKey1 == key || getKey2 == key){
          //If they are and the spot is empty
          if(thePredator[key] == "our empty soul"){
            
            //Push the spot onto the queue to contiune and the Predator to hunt down more of the filthy alien menace
            theQueue.push(key);
            thePredator[key] = frontQueue;
          }
          break;
        }
      }
    }
  }
  
  //Start at the end
  string curr = end;
  
  //WHile we haven't reached the front
  while(curr != start){
    
    //COntiune down the opitalmal path
    path.push_front(thePredator[curr]);
    curr = thePredator[curr];
  }
  
  //End with the end
  path.push_back(end);
  return path;
}


