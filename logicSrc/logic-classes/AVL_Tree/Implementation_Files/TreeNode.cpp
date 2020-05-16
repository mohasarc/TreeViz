#include "../Header_Files/TreeNode.h"

template < class ItemType>
TreeNode<ItemType>::TreeNode(){
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    height = 0;
}

template < class ItemType>
TreeNode<ItemType>::TreeNode( const ItemType& anItem){
    item = anItem;
    leftChildPtr = NULL;
    rightChildPtr = NULL;
    height = 0;
}

template < class ItemType>
TreeNode<ItemType>::TreeNode( const ItemType& anItem, TreeNode<ItemType>* leftPtr, 
                            TreeNode<ItemType>* rightPtr){
    item = anItem;
    leftChildPtr = leftPtr;
    rightChildPtr = rightPtr;
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

// instantiating needed classes 
// not to get a linking time error (undefined reference to)
// read more : https://bytefreaks.net/programming-2/c/c-undefined-reference-to-templated-class-function
template class TreeNode<int>;
template class TreeNode<std::string>;

// int main (){
//     TreeNode<int>* newnd = new TreeNode<int>(4);
//     std::cout << newnd->getItem();
// }