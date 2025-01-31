<<<<<<< HEAD
=======

#include <iostream>
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
<<<<<<< HEAD
    ListNode* head_ = NULL;
    ListNode* tail_ = NULL;
}

=======
    head_ = NULL;
    tail_ = NULL;

}


>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
<<<<<<< HEAD
  return List<T>::ListIterator(tail_);
=======
  return List<T>::ListIterator(NULL);
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode * curr;
  ListNode * nextNode;
  curr = head_;
<<<<<<< HEAD
  do{
    nextNode=curr->next;
    delete curr;
    curr = nextNode;
  }while(curr->next!=0);
=======
  while(curr!=0){
    nextNode=curr->next;
    delete curr;
    curr = nextNode;
  }
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  //newNode -> next = head_;
<<<<<<< HEAD
  if (head_ != NULL) {
    newNode->next = head_;
    head_->prev = newNode;
  }
  if (tail_ == NULL&&head_!=NULL) {
    tail_ = head_;
  }
  head_ = newNode;
=======
  if(head_==NULL){
    head_ = newNode;
    tail_=newNode;
  }
  else {
    newNode->next = head_;
    head_->prev = newNode;
    head_=newNode;
  }
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056

  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  //newNode -> next = head_;
  if(head_==NULL){
      head_= newNode;
<<<<<<< HEAD
  }
  else if (tail_ != NULL) {
    newNode->prev = head_;
    tail_->next = newNode;
    tail_ = newNode;
  }

=======
      tail_= newNode;
//      return;
  }
  else{
    newNode->prev = tail_;
    tail_->next = newNode;
    tail_ = newNode;
  }
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
  length_++;


}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
<<<<<<< HEAD
  ListNode * curr = start;

  for (int i = 0; i < splitPoint || curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL) {
=======
//  ListNode * curr = start;
  //ListNode * returnSplit;
  //ListNode * prevNode;
  //int i=0;


  ListNode * curr = start;
  //return curr;
  for (int i = 0; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr != NULL && curr->prev!=NULL) {
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

<<<<<<< HEAD
  return NULL;
}

=======
  return curr;


  /*
  //base cases
  if(curr==NULL||splitPoint<=0){
    return NULL;
  }
  //std::cout<< "curr->data"<< i<< ":"<<curr->data<< endl;
  //traverse LL
  for(int i=0; i<splitPoint&&curr!=NULL; i++){
    curr = curr->next;
    //std::cout<< "curr->data"<< i<< ":"<<curr->data<< endl;
  }

  //split (curr should be at the location of the start of the new list)
  if (curr != NULL) {
    if(curr->prev==NULL){
      return curr;
    }
      returnSplit = curr;
      prevNode = curr->prev;
  //    std::cout<< "returnSplit->data"<< i<< ":"<<returnSplit->data<< endl;
      //std::cout<< curr->prev->data<< endl;
      //std::cout<< "curr->prev->next->"<< ":"<<curr->prev->next->data<< endl;
      tail_= prevNode;
//      std::cout<< "tail_= curr->prev"<< ":"<<tail_->data<< endl;

//      curr->next = NULL;
      prevNode->next =NULL;
//std::cout<< "returnSplit->prev->data"<< ":"<<prevNode->data<< endl;
      returnSplit->prev =NULL;

      return returnSplit;
  }
  else{
    return curr;
  }*/
}


>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
<<<<<<< HEAD
=======
  //remove
  ListNode * curr;
  ListNode * backNode;
  ListNode * prev;
  curr = head_;
  int i=0;
  while(curr!=NULL&&curr!=tail_&&curr->prev!=NULL){
    if(i%2==1){
      //append to back
      prev = curr->prev;
      backNode= curr;
      curr = curr->next;

      curr->prev = prev;
      prev->next = curr;
      tail_->next=backNode;
      backNode->prev =tail_;
      tail_=backNode;
    }
    else{
      curr = curr->next;
    }
    i++;
  }
  //append to back

>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
<<<<<<< HEAD
=======
  /*ListNode * curr;
  while(curr!=endpoint){

  }*/
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
<<<<<<< HEAD
  return NULL;
=======
  if(first==NULL){
    return second;
  }
  if(second==NULL){
    return first;
  }
  ListNode * prevFront;
  ListNode * firstCurr = first;
  ListNode * secondCurr = second;
  ListNode * returnHead;
  ListNode * next1;
  ListNode * next2;

  while(firstCurr!=NULL&& secondCurr!=NULL){
    //connect previous value
    if(firstCurr!=first){


    }
    next1=firstCurr->next;
    next2=secondCurr->next;
    if(firstCurr->data<secondCurr->data){
      if(firstCurr==first){
        returnHead=first;
        //no need to connect previous value
        prevFront= secondCurr;
        continue;
      }
      firstCurr->next=secondCurr;
      secondCurr->prev=firstCurr;
    }
    else{
      if(secondCurr==second){
        returnHead=second;
        //no need to connect previous value
        prevFront= firstCurr;
      }
      secondCurr->next=firstCurr;
      firstCurr->prev=secondCurr;

    }
    firstCurr=next1;
    secondCurr=next2;
  }
  return returnHead;
>>>>>>> cd122e01498c9773db5cacc4d68d748b4e43f056
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  return NULL;
}
