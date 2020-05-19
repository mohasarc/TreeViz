#ifndef _TREE_AVL
#define _TREE_AVL
#include "TreeNode.h"
#include <iostream>
#include <sstream>
#include <stack>
using namespace std;

template <class T> 
class AVLTree{
private:
// Properties
TreeNode<T>* root;

// Functions
void traverse(TreeNode<T>* root, string &outStr);
bool search(TreeNode<T>* root, T anItem, TreeNode<T>* foundLocation);
void insert(TreeNode<T>* root, T &anItem, TreeNode<T>* &updatePtr);
bool remove(TreeNode<T>* root, T anItem);
// Make the decidsion on which type of rtation is required
void fixAVLTree(TreeNode<T>* aNode, TreeNode<T>* &updatePtr);
// Rotation functions
void rotateR(TreeNode<T>* parent, TreeNode<T>* leftChild);
void rotateL(TreeNode<T>* parent, TreeNode<T>* rightChild);
void rotateRL(TreeNode<T>* parent, TreeNode<T>* rightChild, TreeNode<T>* leftGrandChild);
void rotateLR(TreeNode<T>* parent, TreeNode<T>* leftChild, TreeNode<T>* rightGrandChild);
void updateHeight(TreeNode<T>* cur, int amount);
bool isBalanced(TreeNode<T>* cur);
void toTreeString(TreeNode<T>* root, string &output);
void insert(TreeNode<T> *child, TreeNode<T> *parent);

public:
AVLTree();
string traverse();
bool search(T anItem);
bool insert(T anItem);
bool remove(T anItem);
bool isEmpty();
void constructFromTreeString(const string treeString);
string toTreeString();
};

#endif