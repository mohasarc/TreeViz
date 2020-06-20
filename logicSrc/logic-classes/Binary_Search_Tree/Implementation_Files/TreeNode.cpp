#include "../Header_Files/TreeNode.h"

template <class T>
TreeNode<T>::TreeNode(){
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->leftChildExists = false;
    this->newlyInserted = false;
    this->color = "";
    this->empty = false;
    this->height = 1;
}

template <class T>
TreeNode<T>::TreeNode( const T& anItem){
    this->item = anItem;
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->leftChildExists = false;
    this->newlyInserted = false;
    this->color = "";
    this->empty = false;
    this->height = 1;
}

template <class T>
TreeNode<T>::TreeNode( const T& anItem, TreeNode<T>* leftPtr, TreeNode<T>* rightPtr){
    this->item = anItem;
    this->leftChildPtr = leftPtr;
    this->rightChildPtr = rightPtr;
    this->leftChildExists = false;
    this->newlyInserted = false;
    this->color = "";
    this->empty = false;
    this->height = 1;
}

template <class T>
bool TreeNode<T>::isLeaf() const {
    return this->leftChildPtr == NULL && this->rightChildPtr == NULL;
}

template <class T>
T TreeNode<T>::getItem() const {
    return this->item;
}

template <class T>
void TreeNode<T>::setItem( const T& anItem){
    this->item = anItem;
}

template <class T>
TreeNode<T>* TreeNode<T>::getLeftChildPtr() const {
    return this->leftChildPtr;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRightChildPtr() const {
    return this->rightChildPtr;
}

template <class T>
void TreeNode<T>::setLeftChildPtr(TreeNode<T>* leftPtr){
    this->leftChildPtr = leftPtr;
}

template <class T>
void TreeNode<T>::setRightChildPtr(TreeNode<T>* rightPtr){
    this->rightChildPtr = rightPtr;
}

template <class T>
void TreeNode<T>::setNewlyInserted(bool newlyInserted){
    this->newlyInserted = newlyInserted;
}

template <class T>
bool TreeNode<T>::getNewlyInserted(){
    return this->newlyInserted;
}

template <class T>
void TreeNode<T>::setColor(string color){
    this->color = color;
}

template <class T>
string TreeNode<T>::getColor(){
    return this->color;
}


// int getHeight() const ;
template <class T>// void setHeight(const int h);
void TreeNode<T>::NodeStringParser(string nodeString, T* Values, int &numValues){
    bool nodeFilled = false;
    string aVal = "";
    char aChar;
    numValues = 0;

    for (int i = 0; i < nodeString.length() && !nodeFilled; i++){
        aChar = nodeString.at(i);
        if ((aChar == ',' || aChar == '}') && aVal != ""){
            Values[numValues] = stoi(aVal);
            aVal = "";
            numValues ++;
        } else {
            if (aChar != '{' && aChar != '}' && aChar != '*'){
                aVal += aChar;
            }
        }

        if (aChar == '}'){
            nodeFilled = true;
        }
    }
}

template <class T>
bool TreeNode<T>::construct(const string& nodeString ){ 
    T values[1];
    int numValues;
    
    NodeStringParser(nodeString, values, numValues);
    if (numValues > 0){
        this->item = values[0];
        return true;
    } else 
        return false;
        
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
}

template <class T>
void TreeNode<T>::leftChildExistance(bool leftChildExists){
    this->leftChildExists = leftChildExists;
}

template <class T>
bool TreeNode<T>::doesLeftChildExist(){
    return this->leftChildExists;
}

template <class T>
void TreeNode<T>::setEmpty(bool empty){
    this->empty = empty;
}

template <class T>
bool TreeNode<T>::isEmpty(){
    return this->empty;
}

template <class T>
int TreeNode<T>::getHeight(){
    return this->height;
}

template <class T>
void TreeNode<T>::setHeight(int height){
    this->height = height;
}



template class TreeNode<int>;