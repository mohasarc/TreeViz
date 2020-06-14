#ifndef TREE_NODE_H
#define TREE_NODE_H
#include <string>
#include <iostream>
using namespace std;

template <class T>
class TreeNode
{
private :
    T item; // Data portion
    TreeNode<T>* leftChildPtr; // Left-child pointer
    TreeNode<T>* rightChildPtr; // Right-child pointer
    bool leftChildExists;
    bool newlyInserted;
    string color;
    
public :
    TreeNode();
    TreeNode( const T& anItem);
    TreeNode( const T& anItem, TreeNode<T>* leftPtr, TreeNode<T>* rightPtr);
    bool isLeaf() const ;
    T getItem() const ;
    void setItem( const T& anItem);
    TreeNode<T>* getLeftChildPtr() const ;
    TreeNode<T>* getRightChildPtr() const ;
    void setLeftChildPtr(TreeNode<T>* leftPtr);
    void setRightChildPtr(TreeNode<T>* rightPtr);
    void NodeStringParser(string nodeString, T* Values, int &numValues);
    bool construct(const string& nodeString );
    void leftChildExistance(bool leftChildExists);
    bool doesLeftChildExist();
    void setNewlyInserted(bool newlyInserted);
    bool getNewlyInserted();
    void setColor(string color);
    string getColor();
};

#endif