/**
 * @author Mohammed S. Yaseen
 * @date 7/6/2020
 * */

#ifndef BTREE_H
#define BTREE_H
#include "./BNode.h"
#include <sstream>
#include <stack>
#include <cmath>

template <class type>
class BTree{
private:
    BNode<type>* root;
    int degree;
    bool propagateS;
    bool prioritizeInorderPredecessor;
    bool prioritizeRotatingLeft;
    int minNumKeys;
    int maxNumKeys;

    // Private functions
    void insert(type key, BNode<type>* curNode, BNode<type>* parentNode);
    void balance(BNode<type>* child, BNode<type>* parent);
    void split(BNode<type>* child, BNode<type>* parent, int splitIndex);
    void traverse(BNode<type>* curNode, int level);
    void remove(type key, BNode<type>* curNode, BNode<type>* parentNode);
    bool rotate(BNode<type>* child, BNode<type>* parent);
    bool rotateL(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent);
    bool rotateR(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent);
    void merge(BNode<type>* child, BNode<type>* parent);
    bool findInorderSuccessor(type key, type &successorKey, BNode<type>* curNode, bool forceExtraction);
    bool findInorderPredecessor(type key, type &predecessorKey, BNode<type>* curNode, bool forceExtraction);
    bool isValidBTreeString(string bTreeString);
    // TreeViz specific functions
    void toTreeString(BNode<type>* curNode, string &output);
    void insert(BNode<type>* child, BNode<type>* parent);

public:
    BTree(int degree);
    ~BTree();
    void insert(type key);
    void remove(type key);
    bool find(type key);
    void traverse();
    // TreeViz specific functions
    string toTreeString();
    void constructFromTreeString(string treeString);
};
#endif