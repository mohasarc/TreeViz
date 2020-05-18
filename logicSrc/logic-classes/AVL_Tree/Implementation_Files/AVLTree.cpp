#include "../Header_Files/AVLTree.h"

template <class T>
AVLTree<T>::AVLTree(){
    root = NULL;
}

template <class T>
string AVLTree<T>::traverse(){
    string output = "";
    traverse(root, output);
    return output;
}

template <class T>
void AVLTree<T>::traverse(TreeNode<T>* root, string &outStr){
    if (root == NULL)
        return;
    std::ostringstream oss;

    if (root->isLeaf()){
        oss << root->getItem() << "\t";
        outStr += oss.str();
        oss.str("");
        oss.clear();
        // cout << root->getItem() << "\t";
        return;
    }

    traverse(root->getLeftChildPtr(), outStr);

    oss << root->getItem() << "\t";
    outStr += oss.str();
    oss.str("");
    oss.clear();
    // cout << root->getItem() << "\t" ;

    traverse(root->getRightChildPtr(), outStr);
}

template <class T>
bool AVLTree<T>::search(T anItem){

}

template <class T>
bool AVLTree<T>::search(TreeNode<T>* root, T anItem, TreeNode<T>* foundLocation){
    
}

template <class T>
bool AVLTree<T>::insert(T anItem){
    TreeNode<T>* updatedPtr;
    insert(root, anItem, updatedPtr);

    return true; // HARD CODED -- Might need to be changed
}

template <class T>
void AVLTree<T>::insert(TreeNode<T>* cur, T &anItem, TreeNode<T>* &updatePtr){
    cout << "in insert" << endl;
    // If empty insert at root
    if (isEmpty()){
        root = new TreeNode<T>(anItem);
        cout << "inserting at root " << root->getItem() << endl;
        return;
    }

    // Find the location to insert
    // Not Leaf
    if (!cur->isLeaf()){
        cout << "not a leaf" << endl;
        if (anItem < cur->getItem()){
            // Smaller, go left
            if (cur->getLeftChildPtr() != NULL){
                insert(cur->getLeftChildPtr(), anItem, updatePtr);
                // when returning update the pointer to left
                cout << "updating left pointer of " << cur->getItem() << endl;
                cout << "was " << cur->getLeftChildPtr()->getItem() << endl;
                cur->setLeftChildPtr(updatePtr);
                cout << "became " << cur->getLeftChildPtr()->getItem() << endl;

            }
            else {
                cur->setLeftChildPtr(new TreeNode<T>(anItem));
            }

        } else {
            if (cur->getRightChildPtr() != NULL){
                // Larger, go right
                insert(cur->getRightChildPtr(), anItem, updatePtr);
                // when returning update the pointer to right
                

                cout << "updating right pointer of " << cur->getItem() << endl;
                cout << "was " << cur->getRightChildPtr()->getItem() << endl;
                cur->setRightChildPtr(updatePtr);
                cout << "became " << cur->getRightChildPtr()->getItem() << endl;
            }
            else {
                cur->setRightChildPtr(new TreeNode<T>(anItem));
            }

        }
    }
    // Leaf OR returning
    else {
        // Leaf node
        cout << "insering at a leaf node " << endl;
        if (anItem < cur->getItem())
            cur->setLeftChildPtr(new TreeNode<T>(anItem));
        else 
            cur->setRightChildPtr(new TreeNode<T>(anItem));
    }

    // Returning
    cout << "returning" << endl;
    updateHeight(cur, 1);
    cout << "height updated " << endl;
    if (!isBalanced(cur)){
        cout << "tree is not balanced " << endl;
        fixAVLTree(cur, updatePtr);
    } else {
        cout << "tree is balanced" << endl;
        updatePtr = cur;
    }
    
    if (cur == root){
        cout << "updating root " << endl;
        cout << "old root " << root->getItem() << endl;
        root = updatePtr;
        cout << "new root " << root->getItem() << endl;
    }
}

template <class T>
bool AVLTree<T>::remove(T anItem){
    return false;
}

template <class T>
bool AVLTree<T>::isEmpty(){
    return !root;
}

template <class T>
void AVLTree<T>::updateHeight(TreeNode<T>* cur, int amount){
    int lChildHeight;
    int rChildHeight;
    int maxHeight;

    // initializing variables
    cur->getLeftChildPtr() ? lChildHeight = cur->getLeftChildPtr()->getHeight() : lChildHeight = 0;
    cur->getRightChildPtr() ? rChildHeight = cur->getRightChildPtr()->getHeight() : rChildHeight = 0;
    lChildHeight > rChildHeight ? maxHeight = lChildHeight : maxHeight = rChildHeight;
    cur->setHeight(maxHeight + amount);
}

template <class T>
bool AVLTree<T>::isBalanced(TreeNode<T>* cur){
    bool violates = false;
    cout << "checking balance" << endl;

    if (cur == NULL)
        return true;

    if (cur->getHeight() >= 2){
        if (cur->getLeftChildPtr() == NULL)
            return false;
        if (cur->getRightChildPtr() == NULL)
            return false;

        cur->getRightChildPtr()->getHeight() - cur->getLeftChildPtr()->getHeight() >= 2 ||
        cur->getRightChildPtr()->getHeight() - cur->getLeftChildPtr()->getHeight() <= -2 
        ? violates = true : violates = false;
    }
    
    cout << "is balanced " << !violates << endl;
    return !violates;
}

template <class T>
void AVLTree<T>::fixAVLTree(TreeNode<T>* aNode, TreeNode<T>* &updatePtr){
    cout << "in fixing avl tree" << endl;

    // Local variables
    int lChildHeight;
    int rChildHeight;
    bool lChildBalanced;
    bool rChildBalanced;

    // initializing variables
    aNode->getLeftChildPtr() ? lChildHeight = aNode->getLeftChildPtr()->getHeight() : lChildHeight = 0;
    aNode->getRightChildPtr() ? rChildHeight = aNode->getRightChildPtr()->getHeight() : rChildHeight = 0;
    lChildBalanced = isBalanced(aNode->getLeftChildPtr());
    rChildBalanced = isBalanced(aNode->getLeftChildPtr());

    // Decide how to fix it
    if (lChildHeight > rChildHeight && lChildBalanced){
        // Perform a right rotate
        cout << "Perform a right rotate" << endl;
        updatePtr = aNode->getLeftChildPtr();
        rotateR(aNode, aNode->getLeftChildPtr());
    } else if (rChildHeight > lChildHeight && rChildBalanced){
        // Perform a left rotate
        cout << "Perform a left rotate" << endl;
        updatePtr = aNode->getRightChildPtr();
        rotateL(aNode, aNode->getRightChildPtr());
    } else if (lChildHeight > rChildHeight && !lChildBalanced){
        // Perform a left right rotate
        cout << "Perform a left right rotate" << endl;
        updatePtr = aNode->getLeftChildPtr();
        rotateLR(aNode, aNode->getLeftChildPtr(), aNode->getLeftChildPtr()->getRightChildPtr());
    } else if (rChildHeight > lChildHeight && !rChildBalanced){
        // Perform a right left rotate
        cout << "Perform a right left rotate" << endl;
        updatePtr = aNode->getRightChildPtr();
        rotateRL(aNode, aNode->getRightChildPtr(), aNode->getRightChildPtr()->getLeftChildPtr());
    }
}

// Rotation functions
template <class T>
void AVLTree<T>::rotateR(TreeNode<T>* parent, TreeNode<T>* leftChild){
    TreeNode<T>* tmp = leftChild->getRightChildPtr();
    leftChild->setRightChildPtr(parent);
    parent->setLeftChildPtr(tmp);
}

template <class T>
void AVLTree<T>::rotateL(TreeNode<T>* parent, TreeNode<T>* rightChild){
    TreeNode<T>* tmp = rightChild->getLeftChildPtr();
    rightChild->setLeftChildPtr(parent);
    parent->setRightChildPtr(tmp);
}

/**
 * 
 * rightChild should be saved before the function call or it will be lost
 * */
template <class T>
void AVLTree<T>::rotateRL(TreeNode<T>* parent, TreeNode<T>* rightChild, TreeNode<T>* leftGrandChild){
    TreeNode<T>* updatePtr = leftGrandChild;
    rotateR(rightChild, leftGrandChild);
    parent->setRightChildPtr(updatePtr);
    rotateL(parent, rightChild);
}

template <class T>
void AVLTree<T>::rotateLR(TreeNode<T>* parent, TreeNode<T>* leftChild, TreeNode<T>* rightGrandChild){
    TreeNode<T>* updatePtr = rightGrandChild;
    rotateR(leftChild, rightGrandChild);
    parent->setRightChildPtr(updatePtr);
    rotateL(parent, leftChild);
}

template <class T>
void AVLTree<T>::toTreeString(TreeNode<T>* root, string &output){
    std::ostringstream oss;
    // Base case 1
    if (root == NULL){
        // Empty node {}
        oss << "{";
        oss << "}";
        output += oss.str();
        oss.str("");
        oss.clear();
        return;
    }

    // Base Case 2
    if (root->isLeaf()){
        // wrap its contents with {}
        oss << "{";
        oss << root->getItem();
        oss << "}";
        output += oss.str();
        oss.str("");
        oss.clear();
        return;
    }

    // Not a leaf
    // *** add self ***
    oss << "{";
    oss << root->getItem();
    oss << "}";

    // add Left child
    oss << "(";
    output += oss.str();
    oss.str("");
    oss.clear();
    toTreeString(root->getLeftChildPtr(), output);

    // add Right child
    oss << ",";
    output += oss.str();
    oss.str("");
    oss.clear();
    toTreeString(root->getRightChildPtr(), output);

    oss << ")";
    output += oss.str();
    oss.str("");
    oss.clear();
}

template <class T>
void AVLTree<T>::insert(TreeNode<T> *child, TreeNode<T> *parent){
    cout << "in insert method" << endl;
    if (parent == NULL){
        root = child;
        return;
    }

    cout << "deciding where to insert" << endl;
    if (parent->getLeftChildPtr() == NULL && !parent->doeshaveLeftChild()){
        cout << "adding to left child " << endl;
        parent->setLeftChildPtr(child);
        cout << "left child was set" << endl;
        parent->setHasLeftChild(true);
        cout << "has left was set" << endl;
    } else if (parent->getRightChildPtr() == NULL){
        cout << "adding to right child" << endl;
        parent->setRightChildPtr(child);
    }
}

template <class T>
void AVLTree<T>::constructFromTreeString(const string treeString){
    cout << "in constructFromTreeString function " << endl;
    stack<TreeNode<T>*> parentsStack;
    TreeNode<T>* tmpNode;

    for (int i = 0; i < treeString.length(); i++){
        cout << " from for " << parentsStack.size() << "   " << treeString[i] << endl;
        switch (treeString.at(i))
        {
        case '{':
        tmpNode = new TreeNode<T>();
        tmpNode->construct(treeString.substr(i));
            if (root == NULL){
                cout << "inserting node at root" << endl;
                insert(tmpNode, NULL);
            } else {
                cout << "inserting node at its parent" << endl;
                cout << tmpNode->getItem() << endl;
                cout << "gotten item" << endl;
                cout << parentsStack.size() << endl;
                cout << parentsStack.top() << endl;
                cout << (parentsStack.top())->getItem() << endl;
                insert(tmpNode, parentsStack.top());
                cout << "WAS INSERTED" << endl;
            }

            // update stack
            parentsStack.push(tmpNode);
            cout << parentsStack.size() << endl;
            cout << parentsStack.top() << endl;
            cout << (parentsStack.top())->getItem() << endl;
            cout << "PUSHED TO STACK" << endl;
        break;

        case '}':
            // if node has no children pop it from parents
            if (treeString[i+1] != '('){
                cout << "popping the stack" << endl;
                parentsStack.pop();
            }
            break;

        case '(':
            break;

        case ',':
            /* code */
            break;

        case ')':
            // node has finished so pop it from parents stack
            cout << " ) ";
            cout << parentsStack.size() << endl;
            cout << "popping" << endl;
            parentsStack.pop();
            break;

        default:
            break;
        }
    }

    cout << "finished proessing string" << endl;
}

template <class T>
string AVLTree<T>::toTreeString(){
    string outStr = "";
    this->toTreeString(root, outStr);
    return outStr;
}

template class AVLTree<int>;
template class AVLTree<string>;

// int main (){
//     AVLTree<int>* node = new AVLTree<int>();
//     node->insert(10);
//     node->insert(5);
//     node->insert(2);
//     node->insert(3);
//     node->insert(7);
//     node->insert(1);
//     node->traverse();
//     return 0;
// }