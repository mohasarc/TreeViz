#ifndef _TREE_23
#define _TREE_23
#include "TriNode.h"
#include <iostream>
#include <stack>
using namespace std;

template <class T> 
class Tree23{
private:
// Properties
TriNode<T>* root;

// Methods
void traverse(TriNode<T>* root, string &output);
bool search(TriNode<T>* root, T anItem, TriNode<T>* foundLocation);
void insert(TriNode<T>* root, T &anItem, TriNode<T>* &newPtr);
bool remove(TriNode<T>* root, T anItem);
void swapWithChild(TriNode<T>* root, T &anItem, char which);
void splitNode(TriNode<T>* origNode, TriNode<T>* &separatedNode, TriNode<T>* newNode);
void toTreeString(TriNode<T>* root, string &output);
void insert(TriNode<T> *Parent, TriNode<T> *child);
// This method has to be implemented in the header file
// not to get a linkage error
/**
 * This function takes a function and its arguments to update all
 * entries using the given function
 * @param cur The index of the current entry (used for the recursive call)
 * @param fcn The function that will be used to update all entries
 * @param args The parameters that the fcn function take (parameter packs)
 * */
template <typename Function, typename... Args>
void updateEntries(TriNode<T>* curNode,Function fcn, Args... args){
    // Base Case
    if (curNode->isLeaf()){
        // Apply the function
        curNode->setSmallItem(
            fcn(curNode->getSmallItem(), args...)
        );

        if (curNode->isThreeNode()){
            curNode->setLargeItem(
                fcn(curNode->getLargeItem(), args...)
            );
        }
        return;
    }

    // Not a leaf
    // Go Left
    updateEntries(curNode->getLeftChildPtr(), fcn, args...);

    // Apply function to smaller Item
    curNode->setSmallItem(
        fcn(curNode->getSmallItem(), args...)
    );

    // Go middle
    updateEntries(curNode->getMidChildPtr(), fcn, args...);

    if (curNode->isThreeNode()) {
        // Apply function on large item
        curNode->setLargeItem(
            fcn(curNode->getLargeItem(), args...)
        );

        // Go right
        updateEntries(curNode->getRightChildPtr(), fcn, args...);
    }
}
public:
Tree23();
string traverse();
string toTreeString();
bool search(T anItem);
bool insert(T anItem);
bool remove(T anItem);
void constructFromTreeString(string treeString);
// This method has to be implemented in the header file
// not to get a linkage error
/**
 * This function takes a function and its arguments to update all
 * entries using the given function
 * @param fcn The function that will be used to update all entries 
 *            (First argument should always be of the type of the entries)
 * @param args The parameters that the fcn function take (parameter packs)
 * */
template<typename Function, typename... Args>
void updateEntries(Function fcn, Args... args){
    updateEntries(root, fcn, args...);
}
};
#endif