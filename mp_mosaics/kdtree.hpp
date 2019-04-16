/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;
#include <cmath>

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
    // if(!first[curDim] || !second[curDim]){
    //   return false;
    // }
     if(first[curDim] == second[curDim]){
       return (first<second);
     } else{
       if(first[curDim] < second[curDim]){
         return true;
       } else{
         return false;
       }
     }
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     
  double curD = getDistance(target,currentBest);
  double potD = getDistance(target,potential);
  
     if(curD == potD){
       return (potential < currentBest);
     } else {
       if(potD < curD){
         return true;
       } else if(curD < potD){
         return false;
       }
     }
   return false;
}

template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& first,const Point<Dim>& second) const{
  double dist = 0;
  for(int i = 0; i < Dim; i++){
    dist += pow((first[i] - second[i]),2);
  }
  return dist;
}
  
template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
  
   kdpoints = newPoints;
   /*
   for(int i = 0; i < newPoints.size(); i++){
     kdpoints[i] =newPoints[i]);
   }
    */
  /*
    if(kdpoints.size() > 1){
       buildTheTree(0,kdpoints.size()-1,0);
     }
   */
  //cout << kdpoints.size() << " this" << endl;
 // cout << Dim << " this2" << endl;
  //cout <<"Hello8" << endl;
 // for(unsigned i = 0; i < kdpoints.size(); i++){
   // cout << kdpoints[i] << endl;
  //}
  if(kdpoints.size() == 1){
    return;
  }
  buildTheTree(/*root,*/ 0,int(kdpoints.size()-1),0);
  //root = new KDTreeNode(int(kdpoints.size()-1)/2);
  root = NULL;
  insert(root,0,kdpoints.size()-1);
  //cout << "hello root " << root->point << endl;
  //cout << "hello root " << root->left->point << endl;
  //for(unsigned i = 0; i < kdpoints.size(); i++){
  //  cout << kdpoints[i] << endl;
  //}
  //cout <<"Hello19" << edl;
  return; 
}
template <int Dim>
void KDTree<Dim>::insert(KDTreeNode *&subRoot, int start, int end){
  //cout << "start " <<start << endl;
  //cout << "end " <<end << endl;
  if(start == end){
    subRoot = new KDTreeNode(kdpoints[start]);
    //cout << "point " << kdpoints[start] << endl;
   // return subRoot;
   return;
  }
  if(start > end){
    //return subRoot;
    return;
  }
  int midPoint = (start+end)/2;
  //cout << "midP " <<midPoint << endl;
  //cout <<"Hello19" << endl;
  //if(subRoot == NULL){
 // cout << "point " << kdpoints[midPoint] << endl;
  subRoot = new KDTreeNode(kdpoints[midPoint]);
    //subRoot(kdpoints[midPoint]);
  //  cout << "root " << subRoot->point << endl;
  //}
  int midLeft = midPoint-1;
  int midRight = midPoint+1;
  insert(subRoot->left,start,midLeft);
  insert(subRoot->right,midRight,end);
  //return subRoot;
}

template <int Dim>
void KDTree<Dim>::buildTheTree(/*KDTreeNode *subRoot,*/int startL,int endR,int dimen){
  //cout <<"Hello10" << endl;
  if(startL >= endR){
    return;
  }
  int getMid = (startL+endR)/2;
  quickSelectALgo(startL,endR,dimen,getMid);
  int newDim = int((dimen+1)%Dim);
  //cout <<"Hello9" << endl;
    
 // cout <<"Hello1" << endl;
 // subRoot = new KDTreeNode(quickSelectALgotake2(startL,endR,dimen,getMid));

  //cout << "point " << subRoot->point << endl;
    //int newDim = int((dimen+1)%Dim);
    /*
    */
   // 
     // cout <<"Hello11" << endl;
    //   buildTheTree(/*subRoot->left,*/startL,getMid-1, (dimen+1)%Dim);
     //  cout <<"Hello12" << endl;
    //}
    buildTheTree(startL,getMid-1, newDim);
   // i
    //cout <<"Hello6" << endl
      //cout <<"Hello14" << endl;
      buildTheTree(getMid+1, endR, newDim);
      //cout <<"Hello13" << endl;
   // }
   // cout <<"Hello7" << endl;
     return;
}

template <int Dim>
void KDTree<Dim>::quickSelectALgo(int startL,int endR,int dimen,int getMid){
  if(startL >= endR){
    return;
  }
  int getM = (startL+endR)/2;
  Point<Dim> p = kdpoints[getM];
  int part = startL;
  //cout <<"Hello16" << endl;
  std::swap(kdpoints[getM], kdpoints[endR]);
  //cout <<"Hello4" << endl;
  for(int i = startL; i < endR; i++){
    if(smallerDimVal(kdpoints[i],p, dimen)){
      //  cout <<"Hello17" << endl;
      std::swap(kdpoints[part], kdpoints[i]);
      part++;
    }
  }
  //cout <<"Hello5" << endl;
  std::swap(kdpoints[part], kdpoints[endR]);
  //cout <<"Hello18" << endl;
  
  if(part < getMid){
    //cout <<"Hello15" << endl;
    return quickSelectALgo(part+1,endR,dimen,getMid);
  }
  if(part > getMid){
    return quickSelectALgo(startL,part-1,dimen,getMid);
  }
  /*
 // cout <<"Hello3" << endl;
  //
  //
    //cout <<"Hello14" << endl;
 // }
  //
    //cout <<"Hello15" << endl;
  //  return quickSelectALgo(startL,pos-1,dimen, getMid);
  //}
  
    return quickSelectALgo(pos + 1,endR,dimen, getMid);
  } else if(pos > getMid){
   */
}


template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other) {
  /**
   * @todo Implement this function!
   */
  
  //DestoryRecurs(root);
  size = other.size;
  copy(root,other.root);
  kdpoints = other.kdpoints;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs) {
  /**
   * @todo Implement this function!
   */
  if (this != & rhs) {
    DestoryRecurs(root);
    size = rhs.size;
    copy(root,rhs.root);
    kdpoints = rhs.kdpoints; 
  }
  
  return *this;
}
template <int Dim>
void KDTree<Dim>::copy(KDTreeNode *&subrootOurs,KDTreeNode *other)
{
  if (other == NULL) {
    return;
  }
  
  subrootOurs = new KDTreeNode(other->point);
  copy(subrootOurs->left,other->left);
  copy(subrootOurs->right,other->right);
}


template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
 DestoryRecurs(root);
  size = 0;
}

template <int Dim>
void KDTree<Dim>::DestoryRecurs(KDTreeNode *&subNode){
  if(subNode){
    DestoryRecurs(subNode->left);
    DestoryRecurs(subNode->right);
    delete subNode;
    subNode = NULL;
  }
  return;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    
    int right = kdpoints.size() - 1;
    int left = 0;
    double dist = 0.0 ;
    bool first = true;
    Point<Dim> currentBest;
    fNNHelper(query,left,right,0,dist,first,currentBest);
    return currentBest;
    //return Point<Dim>();
     
    //Point<Dim> currentBest;
//  return Point<Dim>();
}

template <int Dim>
void KDTree<Dim>::fNNHelper(const Point<Dim>& query,int startL,int endR,
                            int dimen, double& dist,bool & first,Point<Dim>& currentBest) const{
  
  if(startL > endR){
    return;
  } else if(startL == endR){
    if(first == false){
      if(shouldReplace(query,currentBest,kdpoints[startL])){
        currentBest = kdpoints[startL];
        dist = getDistance(currentBest, query);
      }
    } else{
      currentBest = kdpoints[startL];
      dist = getDistance(query, currentBest);
      first = false;
    }
  
  return;
  } else {
  int getMid = (startL+endR)/2;
  int one = 0;
  int two = 0;
  int recursOne = 0;
  int recurseTwo = 0;
  if(smallerDimVal(query,kdpoints[getMid], dimen) ==  true){
    recursOne = startL;
    recurseTwo = getMid-1;
    one = getMid+1;
    two = endR;
  } else{
    recursOne = getMid+1;
    recurseTwo = endR;
    one = startL;
    two = getMid-1;
  }
  int newDim = (dimen+1)%Dim;
  fNNHelper(query, recursOne, recurseTwo, newDim, dist, first, currentBest);
  if(shouldReplace(query,currentBest,kdpoints[getMid]) == true){
    currentBest = kdpoints[getMid];
    dist = getDistance(currentBest,query);
    first = false;
  }
  int getNewDist = pow((kdpoints[getMid][dimen]- query[dimen]),2);
  if(getNewDist <= dist){
    fNNHelper(query, one, two, newDim, dist, first, currentBest);
  }
  }
}
   

