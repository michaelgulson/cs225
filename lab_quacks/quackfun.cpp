/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */
 #include <string.h>
 #include <cmath>

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
   T sum=T();
   T first;
    // base case empty stack
    if(s.size() < 1){
      return sum;
    }
    //base case one element on stack
  /*  else if(s.size()==1){
      sum = s.top();
      return sum;
    }

    else if(s.size()==2){
      first = s.top();
      s.pop();
      second = s.top();
      s.pop();
      sum = first + second;
      s.push(second);
      s.push(first);
      return sum;
    }*/
    else{
      first = s.top();
      s.pop();
      sum = first + QuackFun::sum(s);
    //  s.push(second);
      s.push(first);
      return sum;
    }
    //return T(); // stub return value (0 for primitive types). Change this!
    // Note: T() is the default value for objects, and 0 for primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{
  stack<char> s;
  /*while(input.empty()!=true){
    frontQueue = input.front();
    if(strncmp(frontQueue,"[",2)==0){
      s.push(1);
    }
    else if(strncmp(frontQueue,"[",2)==0){
      s.push(-1);
    }
    input.pop();
  }*/
  while(input.empty()!=true){
    //frontQueue = input.front();
    if(input.front()=='['){
      s.push('[');
    }
    else if(input.front()==']'){
      if(s.empty())
        return false;
      s.pop();
    }
    input.pop();
  }


/*  while(s.empty()!=true){
    s.top();
    s.pop();
    balance+=topStack;
    if(balance<0){
      return false;
    }
  }*/
  if(s.empty()){
    return true;
  }
  else{
    return false;
  }

}

/*
void scramble_helper(bool underFive, int size, stack<T> * s, queue<T> & q){
  //since stack passed as ptr, changed member functions to ->

  if(underFive){
    for(int i=0; i<size; i++){
      if(i%2==1){
        for(int j=0; j<i; j++){
          T temp = q.front();
          q.push(temp);
          q.pop();
        }
      }
    else{
      for(int j=0; j<i; j++){
        T temp = q.front();
        s->push(temp);
        q.pop();
      }
      for(int j=0; j<i; j++){
        temp = s.front();
        s->pop();
        q.push(temp);
      }
    }
  }
}
else
  while(cntFive<5){
    if(i%2==1){
      for(int j=0; j<i; j++){
        T temp = q.front();
        q.push(temp);
        q.pop();
      }
    }
    else{
      for(int j=0; j<i; j++){
        T temp = q.front();
        s->push(temp);
        q.pop();
      }
      for(int j=0; j<i; j++){
        temp = s->front();
        s->pop();
        q.push(temp);
      }
    }
    i++;
    cntFive++;
}


*/

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
  /*  stack<T> s;
    int modFive, qSize, cntDivFive, cntFive;
    bool underFive=false;
    qSize = q.size();
    cntDivFive = ceil(double(qsize)/double(5));
    for(int i=0; i<cntDivFive; i++){
      if(qSize/5<1){
        underFive= true
        scramble_helper(underFive, qSize, &s,q);
      }
      else{
        scramble_helper(underFive, 0, &s, q);
      }
      qSize= qSize-5;
    }
*/
    /*for(int i= 1; i<6; i++){
      if(i%2==1){
        for(int j=0; j<i; j++){
          T temp = q.front();
          q.push(temp);
          q.pop();
        }
      }
      else{
        for(int j=0; j<i; j++){
          T temp = q.front();
          s.push(temp);
          q.pop();
        }
        for(int j=0; j<i; j++){
          temp = s.front();
          s.pop();
          q.push(temp);
        }
      }
    }*/
    /*int i =0;
    while(cntFive<5){
      if(i%2==1){
        for(int j=0; j<i; j++){
          T temp = q.front();
          q.push(temp);
          q.pop();
        }
      }
      else{
        for(int j=0; j<i; j++){
          T temp = q.front();
          s.push(temp);
          q.pop();
        }
        for(int j=0; j<i; j++){
          temp = s.front();
          s.pop();
          q.push(temp);
        }
        i++;
        cntFive++;
      }*/
    stack<T> s;
    int blockSize=1;
    int cnt=q.size();
    T temp;
    while(cnt>0){
      if(blockSize>cnt){
          if(blockSize%2==1){
            for(int j=0; j<blockSize; j++){
                temp = q.front();
                q.push(temp);
                q.pop();
              }
            }
            else{
              for(int j=0; j<blockSize; j++){
                temp = q.front();
                s.push(temp);
                q.pop();
              }
              for(int j=0; j<blockSize; j++){
                temp = s.top();
                s.pop();
                q.push(temp);
              }
            }
          }
        else{
            if(blockSize%2==1){
              for(int j=0; j<blockSize; j++){
                  T temp = q.front();
                  q.push(temp);
                  q.pop();
                }
              }
              else{
                for(int j=0; j<blockSize; j++){
                  T temp = q.front();
                  s.push(temp);
                  q.pop();
                }
                for(int j=0; j<blockSize; j++){
                  temp = s.top();
                  s.pop();
                  q.push(temp);
                }
              }
          }
          cnt=cnt-blockSize;
          blockSize++;

  }
    // optional: queue<T> q2;
    //block size variable starting at 1 increment
    //
    // Your code here
}

/**
 * Checks if the parameter stack and queue are the same. A stack and a queue
 * are considered to the "the same" if they contain only elements of exactly
 * the same values in exactly the same order.
 *
 * @note You may assume the stack and queue contain the same number of items!
 *
 * @note The back of the queue corresponds to the top of the stack!
 *
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 *
 * @param s The stack to compare
 * @param q The queue to compare
 * @return  true if the stack and the queue are the same; false otherwise
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    bool retval = true; // optional
    // T temp1; // rename me
    // T temp2; // rename :)

    // Your code here

    return retval;
}

}
