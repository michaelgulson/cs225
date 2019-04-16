
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    //return 0;
    //Could use 1 or 0 but 1 seems to be easier
    size_t rootNum = 1;
    return rootNum;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    //2*currentIdx + 1
    //Since we are using 1 as root, this is the left child number
    size_t lChild = 2*currentIdx;
    return lChild;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    //2currentIdx + 2
    //SInce we are using 1 as root, this is right child
    size_t rChild = (2*currentIdx)+1;
    return rChild;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    //floor((currentIdx-1)/2)
    //since we are using root 1, this is parent
    size_t paren = floor(currentIdx/2);
    return paren;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    
    //Need to check if the currentIdx is not a leaf node, if its not return true
    size_t getChild = (currentIdx*2);
    if(getChild <_elems.size()){
      return true;
    }
    //if it is a lead node, it doesn't have a child
    return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    //Gets left and right child
    size_t lChild = leftChild(currentIdx);
    size_t rChild = rightChild(currentIdx);
    //Checks to make sure it has a child
    if(hasAChild(currentIdx) == true){
      //if it does, checks to see if lCHild is higherPriority
      if(rChild >= _elems.size()){
        return lChild;
      }
      if(higherPriority(_elems[lChild],_elems[rChild])){// == true){ //CHANGE
        return lChild;
      }
      
    }
    //if left child isn't return rightChild, since we don't have to recheck everything
    //we can just return rChild
    return rChild;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //First make sure it has a child so that it can heapifyDown
    if(hasAChild(currentIdx) == true){
      //Find the maxPriorityChild and use that to heapify down
      size_t findMin = maxPriorityChild(currentIdx);
      
      //CHeck to make sure the child has a higherPriority then the current, if so swap and keep
      //going down
      if(higherPriority(_elems[findMin],_elems[currentIdx]) == true){
        std::swap(_elems[findMin],_elems[currentIdx]);
        heapifyDown(findMin);
      }
    }
    return;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    //Since in this case I am using 1 as root rather then 0, we need
    //to fill 0 with some number that won't ever be touched
    _elems.push_back(std::numeric_limits<T>::min());
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    //As stated in pervious method, since we start with 1, not 0, we need
    //to fill it with a number that won't ever be touched
    _elems.push_back(std::numeric_limits<T>::min());
  
  //Fill the rest of the spots with the rest of the vector
  for(size_t i = 0; i < elems.size(); i++){
    _elems.push_back(elems[i]);
  }
  
  //now we need to start at the parent elemenet then heapify the vector, need 
  //to get it in correct format
  size_t par = parent(elems.size());
  for(size_t i = par; i > 0; i--){
    heapifyDown(i);
  }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    //Check for if the vector is empty
    if(empty() == false){
      
      //if not then since heap starts at 1, we get the 1st element
      T findMin = _elems[1];
      
      //switch elements
      _elems[1] = _elems[_elems.size()-1];
      
      //delete element now that its swithc
      _elems.pop_back();
      
      //Restore heap
      heapifyDown(1);
      return findMin;
    }
    return T();
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    //If not emty
    if(empty() == false){
      
      //Return the root  element, in this case 1
      return _elems[root()];
    }
    return T();
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    
    //Put element in back of the array
    _elems.push_back(elem);
  
    //since last spot, we have to heapify up
    size_t hSize = (_elems.size()-1);
    heapifyUp(hSize);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    
    //CHeck for if idx is out of bounds
    if(idx < _elems.size()){
      
      //Replace element position with elem
      _elems[idx] = elem;
      
      //Restore heap
      heapifyUp(idx);
      heapifyDown(idx);
    }
}


template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    
    //Since we start at 1 spot, if less then 1, since if we have an element vector would
    //be size 2, then if its less then or equal to 1, it is empty.
    if(_elems.size() <= 1){
        return true;
    }
    return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
