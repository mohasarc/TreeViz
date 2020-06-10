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
#include "../../../3rd-Party/deelx.h"

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
    // TreeViz specific functions
    bool isValidBTreeString(string bTreeString);
    void toTreeString(BNode<type>* curNode, string &output);
    void insert(BNode<type>* child, BNode<type>* parent);

public:
    BTree(int degree);
    ~BTree();
    void insert(type key);
    void remove(type key);
    bool find(type key);
    void traverse();
    void setOrder(int order);
    int getOrder();
    void setPropagateS(bool propagateS);
    bool getPropagateS();
    void setPrioritizeInorderPredecessor(bool prioritizeInorderPredecessor);
    bool getPrioritizeInorderPredecessor();
    void setPrioritizeRotateLeft(bool prioritizeRotatingLeft);
    bool getPrioritizeRotateLeft();

    // TreeViz specific functions
    string toTreeString();
    bool insertSequence(string sequence);
    bool constructFromTreeString(string treeString);
};
#endif