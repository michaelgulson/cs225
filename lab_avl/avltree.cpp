/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y =t->right;
    t->right = y->left;
    y->left = t;
    y->height = heightOrNeg1(y->left) + heightOrNeg1(y->right) +1;

    t = y;
    //update height
    //H = HL+HR+!
    t->height = t->left->height + t->right->height +1;


    t->height = heightOrNeg1(t->left) + heightOrNeg1(t->right) +1;

}



template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y =t->left;
    t->left = y->right;
    y->right = t;
    y->height = heightOrNeg1(y->left) + heightOrNeg1(y->right) +1;
    t = y;
    //update height
    //H = HL+HR+!
    t->height = heightOrNeg1(t->left) + heightOrNeg1(t->right) +1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    int balance;  //b=h(Tr)-h(Tl)
    balance = heightOrNeg1(subtree->right)-heightOrNeg1(subtree->left);
    if(balance>=2){
      //elbow check
      if(heightOrNeg1(subtree->right->right) < heightOrNeg1(subtree->right->left)){
        rotateRightLeft(subtree);
      }
      else{
        rotateLeft(subtree);
      }
    }
    else if(balance<=-2){
      //elbow check
      if(heightOrNeg1(subtree->left->left) < heightOrNeg1(subtree->left->right)){
        rotateLeftRight(subtree);
      }
      else{
        rotateRight(subtree);
      }
    }
    else{
      subtree->height = heightOrNeg1(subtree->left) + heightOrNeg1(subtree->right) +1;
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(subtree==NULL){
      subtree= new Node(key, value);
    }
    else if(key<subtree->key){
      //move to left
      insert(subtree->left, key, value);
    }
    else if(key>subtree->key){
      //move to right
      insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
      remove(subtree->left, key);
      rebalance(subtree);
    } else if (key > subtree->key) {
      remove(subtree->right, key);
      rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            Node * leftChild = subtree->left;
            while(leftChild->right!=NULL){
              leftChild = leftChild->right;
            }
            swap(subtree, leftChild);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if(subtree->left==NULL){
              Node * temp = subtree;
              subtree = subtree->right;
              delete temp;

            }
            else{
              Node * temp = subtree;
              subtree = subtree->left;
              delete temp;
            }

        }
        rebalance(subtree);
        // your code here
    }
}
