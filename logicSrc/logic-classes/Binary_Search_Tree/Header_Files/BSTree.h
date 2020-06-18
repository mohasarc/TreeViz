#ifndef BSTree_H
#define BSTree_H
#include "TreeNode.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include "../../../3rd-Party/deelx.h"

using namespace std;

struct Step
{
    string text;
    string treeStr;
    string note;
};

template <class T>
class BSTree{
private:
// Properties
TreeNode<T>* root;
string sequence;
vector<Step> steps;
bool prioritizePredecessor;

// Functions
void traverse(TreeNode<T>* root, string &outStr);
void search(TreeNode<T>* &root, TreeNode<T>* &parent, T anItem);
void insert(TreeNode<T>* root, T &anItem, bool &success);
void removeWithSuccessor(TreeNode<T>* root, TreeNode<T>* parent, bool &success);
void removeWithPredecessor(TreeNode<T>* root, TreeNode<T>* parent, bool &success);
void toTreeString(TreeNode<T>* root, string &output);
TreeNode<T>* getMostLeft(TreeNode<T>* root, TreeNode<T>* &parent);
TreeNode<T>* getMostRight(TreeNode<T>* root, TreeNode<T>* &parent);
string keyToString(T key);
// TreeViz specific functions
void insert(TreeNode<T> *child, TreeNode<T> *parent);
bool isValidBSTreeString(string bsTreeString);
void generateInorderSequence(TreeNode<T>* curNode, string &sequence);
void recordStep(string stepText, string note);

public:
BSTree();
string traverse();
bool search(T anItem);
bool insert(T anItem);
bool remove(T anItem);
bool isEmpty();
void setPrioritizePredecessor(bool prioritizePredecessor);
// TreeViz specific functions
void constructFromTreeString(const string treeString);
string toTreeString();
bool insertSequence(string sequence);
void setSequence(string sequence);
string getSequence();
string generateInorderSequence();
vector<Step> getSteps();
int getStepsNo();
string getStepText(int index);
string getStepTreeStr(int index);
string getStepNote(int index);
void clearSteps();
};

#endif