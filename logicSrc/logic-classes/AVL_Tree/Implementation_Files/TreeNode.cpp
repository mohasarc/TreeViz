#include "../Header_Files/TreeNode.h"

template < class ItemType>
TreeNode<ItemType>::TreeNode(){
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->hasLeftChild = false;
    this->height = 0;
}

template < class ItemType>
TreeNode<ItemType>::TreeNode( const ItemType& anItem){
    this->item = anItem;
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
    this->hasLeftChild = false;
    this->height = 0;
}

template < class ItemType>
TreeNode<ItemType>::TreeNode( const ItemType& anItem, TreeNode<ItemType>* leftPtr, 
                            TreeNode<ItemType>* rightPtr){
    item = anItem;
    leftChildPtr = leftPtr;
    rightChildPtr = rightPtr;
    this->hasLeftChild = false;
    height = 0;
}

template < class ItemType>
bool TreeNode<ItemType>::isLeaf() const {
    // Leaf if has no children
    return !leftChildPtr && !rightChildPtr;
}

template < class ItemType>
ItemType TreeNode<ItemType>::getItem() const {
    return item;
}

template < class ItemType>
void TreeNode<ItemType>::setItem( const ItemType& anItem){
    item = anItem;
}

template < class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getLeftChildPtr() const {
    return leftChildPtr;
}

template < class ItemType>
TreeNode<ItemType>* TreeNode<ItemType>::getRightChildPtr() const {
    return rightChildPtr;
}

template < class ItemType>
void TreeNode<ItemType>::setLeftChildPtr(TreeNode<ItemType>* leftPtr){
    leftChildPtr = leftPtr;
}

template < class ItemType>
void TreeNode<ItemType>::setRightChildPtr(TreeNode<ItemType>* rightPtr){        
    rightChildPtr = rightPtr;
}

template < class ItemType>
int TreeNode<ItemType>::getHeight() const {
    return height;
}

template < class ItemType>
void TreeNode<ItemType>::setHeight(const int h){
    height = h;
}

template < class ItemType>
void TreeNode<ItemType>::NodeStringParser(string nodeString, ItemType* Values, int &numValues){
    bool nodeFilled = false;
    string aVal = "";
    char aChar;
    numValues = 0;

    for (int i = 0; i < nodeString.length(); i++){
        aChar = nodeString.at(i);
        if ((aChar == ',' || aChar == '}') && !nodeFilled){
            Values[numValues] = stoi(aVal);
            aVal = "";
            numValues ++;
        } else {
            if (aChar != '{' && aChar != '}' && !nodeFilled){
                aVal += aChar;
            }
        }

        if (aChar == '}'){
            nodeFilled = true;
        }
    }
}

template < class ItemType>
void TreeNode<ItemType>::construct(const string& nodeString ){
    ItemType values[1];
    int numValues;
    
    NodeStringParser(nodeString, values, numValues);
    if (numValues > 0)
        this->item = values[0];
    this->leftChildPtr = NULL;
    this->rightChildPtr = NULL;
}

template < class ItemType>
bool TreeNode<ItemType>::doeshaveLeftChild(){
    return this->hasLeftChild;
}

template < class ItemType>
void TreeNode<ItemType>::setHasLeftChild(bool hasLeftChild){
    cout << "setting hasleftchild " << endl;
    this->hasLeftChild = hasLeftChild;
}
// instantiating needed classes 
// not to get a linking time error (undefined reference to)
// read more : https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
template class TreeNode<int>;
template class TreeNode<std::string>;

// int main (){
//     TreeNode<int>* newnd = new TreeNode<int>(4);
//     std::cout << newnd->getItem();
// }