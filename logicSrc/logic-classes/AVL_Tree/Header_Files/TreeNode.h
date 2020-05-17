// Author: Mohammed S. Yaseen
// Built upon the code from 25-2_3_Search_Tree/Header_Files/TriNode.h

#ifndef _TRI_NODE
#define _TRI_NODE
#include <iostream>
#include <string>
using namespace std;

template < class ItemType>
class TreeNode
{
private :
ItemType item; // Data portion
TreeNode<ItemType>* leftChildPtr; // Left-child pointer
TreeNode<ItemType>* rightChildPtr; // Right-child pointer
int height;
bool hasLeftChild;

public :
TreeNode();
TreeNode( const ItemType& anItem);
TreeNode( const ItemType& anItem, TreeNode<ItemType>* leftPtr, TreeNode<ItemType>* rightPtr);
bool isLeaf() const ;
ItemType getItem() const ;
void setItem( const ItemType& anItem);
TreeNode<ItemType>* getLeftChildPtr() const ;
TreeNode<ItemType>* getRightChildPtr() const ;
void setLeftChildPtr(TreeNode<ItemType>* leftPtr);
void setRightChildPtr(TreeNode<ItemType>* rightPtr);
int getHeight() const ;
void setHeight(const int h);
void NodeStringParser(string nodeString, ItemType* Values, int &numValues);
void construct(const string& nodeString );
void TreeNode<ItemType>::setHasLeftChild(bool hasLeftChild);
bool doeshaveLeftChild();
}; // end TreeNode

#endif