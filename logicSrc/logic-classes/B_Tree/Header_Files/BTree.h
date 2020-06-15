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

struct Step
{
    string text;
    string treeStr;
};

template <class type>
class BTree{
private:
    BNode<type>* root;
    string sequence;
    int degree;
    bool propagateS;
    bool prioritizeInorderPredecessor;
    bool prioritizeRotatingLeft;
    int minNumKeys;
    int maxNumKeys;
    vector<Step> steps;

    // Private functions
    void insert(type key, BNode<type>* curNode, BNode<type>* parentNode, bool &success);
    void balance(BNode<type>* child, BNode<type>* &parent);
    void split(BNode<type>* child, BNode<type>* parent, int splitIndex);
    void traverse(BNode<type>* curNode, int level);
    void remove(type key, BNode<type>* curNode, BNode<type>* parentNode, bool &success);
    bool rotate(BNode<type>* child, BNode<type>* parent);
    bool rotateL(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent);
    bool rotateR(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent);
    void merge(BNode<type>* child, BNode<type>* parent);
    void findInorderSuccessor(type key, type &successorKey, BNode<type>* &curNode, bool forceExtraction, bool &success);
    void findInorderPredecessor(type key, type &predecessorKey, BNode<type>* &curNode, bool forceExtraction, bool &success);
    string keyToString(type key);
    // TreeViz specific functions
    bool isValidBTreeString(string bTreeString);
    void toTreeString(BNode<type>* curNode, string &output);
    void insert(BNode<type>* child, BNode<type>* parent);
    void generateInorderSequence(BNode<type>* curNode, string &sequence);
    void recordStep(string stepText);

public:
    BTree(int degree);
    ~BTree();
    void insert(type key); // DONE
    void remove(type key); // DONE
    bool find(type key);
    void traverse();  // DONE
    void setOrder(int order);
    int getOrder();
    void setPropagateS(bool propagateS);
    bool getPropagateS();
    void setPrioritizeInorderPredecessor(bool prioritizeInorderPredecessor);
    bool getPrioritizeInorderPredecessor();
    void setPrioritizeRotateLeft(bool prioritizeRotatingLeft);
    bool getPrioritizeRotateLeft();

    // TreeViz specific functions
    string toTreeString(); // DONE
    bool insertSequence(string sequence);
    void setSequence(string sequence);
    string getSequence();
    string generateInorderSequence();
    bool constructFromTreeString(string treeString); // DONE
    vector<Step> getSteps();
    int getStepsNo();
    string getStepText(int index);
    string getStepTreeStr(int index);
    void clearSteps();
};
#endif