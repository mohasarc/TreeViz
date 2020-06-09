/**
 * @author Mohammed S. Yaseen
 * @date 7/6/2020
 * */

#ifndef BNODE_H
#define BNODE_H
#include <vector>
#include <iostream>
#include <string>
using namespace std;

template <class Type>
class BNode {
private:
    vector<Type> keys;
    vector<BNode*> children;
    bool leaf;

public:
    BNode();
    ~BNode();
    void addChild(BNode* aChild, int index);
    void removeChild(BNode* aChild);
    BNode* getChild(int index);
    int getChildNo();
    void addKey(Type key, int index);
    void removeKey(int index);
    Type getKey(int index);
    int getKeyNo();
    void setLeaf(bool leaf);
    bool isLeaf();
    void parseNodeStrig(string nodeString, vector<Type> &keys);
    void construct(const string& nodeString);
};
#endif