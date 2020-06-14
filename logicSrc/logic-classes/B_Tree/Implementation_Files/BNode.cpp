/**
 * @author Mohammed S. Yaseen
 * @date 7/6/2020
 * */

#include "../Header_Files/BNode.h"

/**
 * The constructor
 * */
template <class Type>
BNode<Type>::BNode(){
    this->leaf = false;
}

/**
 * The distructor
 * */
template <class Type>
BNode<Type>::~BNode(){
    for (int i = 0; i < this->children.size(); i++){
        if (this->children.at(i))
            delete this->children.at(i);
    }
}

/**
 * Adds a child at the specified index
 * @param aChild The child to be added
 * @param index The index at which it is being inserted
 * */
template <class Type>
void BNode<Type>::addChild(BNode* aChild, int index){
    this->children.insert(this->children.begin() + index, aChild);
}

/**
 * Erases the child specified
 * @param aChild The child to be erased
 * */
template <class Type>
void BNode<Type>::removeChild(BNode* aChild){
    for (int i = 0; i < this->children.size(); i++){
        if (this->children.at(i) == aChild){
            this->children.erase(this->children.begin() + i);
        }
    }
}

/**
 * @param index The index of the child to be returned
 * @return The child at index
 * */
template <class Type>
BNode<Type>* BNode<Type>::getChild(int index){
    return this->children.at(index);
}

/**
 * @return The number of children
 * */
template <class Type>
int BNode<Type>::getChildNo(){
    return this->children.size();
}

/**
 * @param key The key to be added
 * @param index The index to be added to
 * */
template <class Type>
void BNode<Type>::addKey(Type key, int index){
    this->keys.insert(this->keys.begin() + index, key);
}

/**
 * @param index The index of the key to be deleted
 * */
template <class Type>
Type BNode<Type>::removeKey(int index){
    Type theKey = this->keys[index];
    this->keys.erase(this->keys.begin() + index);
    return theKey;
}

/**
 * To get the value of key at a specific index
 * @param index The index to get its key
 * @return Type the key
 * */
template <class Type>
Type BNode<Type>::getKey(int index){
    return this->keys.at(index);
}

/**
 * @return The number of keys
 * */
template <class Type>
int BNode<Type>::getKeyNo(){
    return this->keys.size();
}

/**
 * To set whether the node a leaf or not
 * @param leaf The new value for leaf
 * */
template <class Type>
void BNode<Type>::setLeaf(bool leaf){
    this->leaf = leaf;
}

/**
 * @return boolean whether the node is a leaf or not
 * */
template <class Type>
bool BNode<Type>::isLeaf(){
    return this->leaf;
}

/**
 * @param nodeString The string to be paresed
 * @param keys The keys that were parsed
 * */
template <class Type>
void BNode<Type>::parseNodeStrig(string nodeString, vector<Type> &keys){
    // Local variables
    bool nodeFilled = false;
    string aKey = "";
    char aChar;

    for (int i = 0; i < nodeString.length() && !nodeFilled; i++){
        aChar = nodeString.at(i);
        if ((aChar == ',' || aChar == '}') && !nodeFilled){
            keys.push_back(stoi(aKey));
            aKey = "";
        } else {
            if (aChar != '{' && aChar != '}'  && aChar != '*'){
                aKey += aChar;
            }
        }

        if (aChar == '}'){
            nodeFilled = true;
        }
    }
}

template <class Type>
void BNode<Type>::construct(const string& nodeString){   
    parseNodeStrig(nodeString, this->keys);
}

template <class Type>
void BNode<Type>::setColor(string color){
    this->color = color;
}

template <class Type>
string BNode<Type>::getColor(){
    return this->color;
}

template class BNode<int>;

// int main(){
//     BNode<int>* node1 = new BNode<int>();
//     BNode<int>* node2 = new BNode<int>();
//     BNode<int>* node3 = new BNode<int>();
//     BNode<int>* node4 = new BNode<int>();
//     BNode<int>* node5 = new BNode<int>();

//     node1->addKey(1, 0);
//     node1->addKey(2, 0);
//     node1->addKey(3, 0);
//     node1->addKey(4, 0);

//     node2->addKey(22, 0);
//     node3->addKey(33, 0);
//     node4->addKey(44, 0);


//     cout << node1->getKey(0) << endl;
//     cout << node1->getKey(1) << endl;
//     cout << node1->getKey(2) << endl;
//     cout << node1->getKey(3) << endl;

//     node1->addChild(node2, 0);
//     node1->addChild(node3, 0);
//     node1->addChild(node4, 1);
//     node1->removeChild(node3);

//     cout << node1->getChild(0)->getKey(0) << endl;
//     cout << node1->getChild(1)->getKey(0) << endl;
//     // cout << node1->getChild(2)->getKey(0) << endl;

//     return 0;
// }