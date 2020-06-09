/**
 * @author Mohammed S. Yaseen
 * @date 7/6/2020
 * */

#include "../Header_Files/BTree.h"

// Plublic functions implementations
/**
 * The constructor
 * */
template <class type>
BTree<type>::BTree(int degree){
    this->degree = degree;
    this->root = NULL;
    this->propagateS = false;
    this->prioritizeInorderPredecessor = false;
    this->prioritizeRotatingLeft = false;
    this->minNumKeys = ceil((double)degree/2) - 1;
    this->maxNumKeys = degree - 1;
}

/**
 * The destructor
 * */
template <class type>
BTree<type>::~BTree(){

}

/**
 * @param key The key to be inserted
 * */
template <class type>
void BTree<type>::insert(type key){
    if (this->root == NULL){
        cout << "creating root" << endl;
        this->root = new BNode<type>();
        this->root->setLeaf(true);
    }

    this->insert(key, this->root, NULL);
}

/**
 * @param key The key to be removed
 * */
template <class type>
void BTree<type>::remove(type key){
    cout << "remove called" << endl;
    remove(key, this->root, NULL);
}

/**
 * @param key The key to be found
 * */
template <class type>
bool BTree<type>::find(type key){

}

/**
 * Traverses the whole tree
 * */
template <class type>
void BTree<type>::traverse(){
    this->traverse(this->root, 0);
}


template <class type>
string BTree<type>::toTreeString(){
    string output = "";
    toTreeString(this->root, output);

    return output;
}

/**
 * Builds the tree out of a tree string
 * @param treeString The treeString describig the tree
 * */
template <class type>
void BTree<type>::constructFromTreeString(string treeString){
    cout << "at construct" << endl;
    stack<BNode<type>*> parentsStack;
    BNode<type>* tmpNode;
    int childCount = 0;

    for (int i = 0; i < treeString.length(); i++){
        switch (treeString.at(i))
        {
        case '{':
        tmpNode = new BNode<type>();
        tmpNode->construct(treeString.substr(i));
            if (root == NULL){
                insert(tmpNode, NULL);
            } else {
                insert(tmpNode, parentsStack.top());
            }

            // update stack
            parentsStack.push(tmpNode);
            break;

        case '}':
            // if node has no children pop it from parents
            if (treeString[i+1] != '(')
                parentsStack.pop();
            break;

        case '(':
            childCount = 0;
            break;

        case ',':
            /* code */
            break;

        case ')':
            // node has finished so pop it from parents stack
            parentsStack.pop();
            break;

        default:
            break;
        }
    }
}

// Private functions implementations
/**
 * 
 * */
template <class type>
void BTree<type>::insert(type key, BNode<type>* curNode, BNode<type>* parentNode){
    cout << "in recursive insert" << endl;
    // Base case
    // -- If leaf insert at it --
    if (curNode->isLeaf()){
        cout << "it is leaf & trying to insert " << key << endl;
        for (int i = 0; i < curNode->getKeyNo(); i++) {
            if (key < curNode->getKey(i)) {
                // insert at it
                curNode->addKey(key, i);
            } else if ( i ==  curNode->getKeyNo() - 1) {
                // insert at it
                cout << "inserting " << key << " at " << i+1 << endl;
                curNode->addKey(key, i + 1);
                break;
            }
        }

        if (curNode->getKeyNo() == 0)
            curNode->addKey(key, 0);

        // May become unbalanced so check balance
        this->balance(curNode, parentNode);

        return;
    }
    
    cout << "not a leaf" << endl;

    // Not leaf
    // Go through current node's children and decide to 
    // which one to go
    for (int i = 0; i < curNode->getKeyNo(); i++) {
        if (key < curNode->getKey(i)) {
            // insert in the tree just before the key greater than it
            insert(key, curNode->getChild(i), curNode);
        }
        else if (i == curNode->getKeyNo() - 1) {
            // Greater than the last key
            insert(key, curNode->getChild(i+1), curNode);
            break;
        }
    }

    // Somewhere at the bottom of the tree balance might have been disrupted
    // so check balance again here (when returning)
    balance(curNode, parentNode);
}

/**
 * Checks if the child node follows the tree rulesand if not balances it
 * @param child The node to be balanced
 * @param parent Its parent node
 * */
template <class type>
void BTree<type>::balance(BNode<type>* child, BNode<type>* parent){
    // Local variables
    int splitIndex = 0;
    int childKeyNo = child->getKeyNo();
    bool rotateSuccessful = false;

    cout << "at balance with " << childKeyNo << " keys " << endl;

    // if the child has more than or equal to degree number of keys it is not balanced
    // (overFull)
    if (childKeyNo > this->degree - 1){
        cout << "not balanced" << endl;
        // Need to perform a split
        // ## calculate the index at which split is performed ##
        // case 1 : having even keys (2 items at the middle)
        if (childKeyNo % 2 == 0) {
            if (this->propagateS){
                // picking the smaller one to propagate upwards
                splitIndex = childKeyNo / 2 - 1;
            } else {
                // picking the larger one to split
                splitIndex = childKeyNo / 2; 
            }
        }
        // case 2 : having odd kids (1 item at the middle)
        else {
            splitIndex = childKeyNo / 2;
        }

        // ## Perform the split ##
        this->split(child, parent, splitIndex);
    }

    // If the child is underfull
    else if (childKeyNo < ( ceil((double)this->degree/2) - 1 ) ){
        cout << "under-full" << endl;
        if (parent){
            // Sol 1. Try borrowing from left or right sbling
            rotateSuccessful = rotate(child, parent);

            // Sol 2. Perform a merge
            if (!rotateSuccessful){
                merge(child, parent);
            }
        }
        // Parent is null means child is the root
        else {
            cout << "parent is null at root" << endl;
            // if root is empty make its child the root
            if (child->getKeyNo() < 1){
                // If there is a child, it'll be the root
                if (child->getChildNo() > 0)
                    this->root = child->getChild(0);
                // if not, The tree got empty
                else 
                    this->root = NULL;
            }
        }
    }
}

/**
 * Splits the child node at splitIndex, propagates item at splitIndex
 * to parent, and link the 2 new nodes to the parent
 * @param child The node to be balanced
 * @param parent Its parent node
 * @param splitIndex The index at which split will be performed
 * */
template <class type>
void BTree<type>::split(BNode<type>* child, BNode<type>* parent, int splitIndex){
    cout << "at split with split index " << splitIndex << endl;
    // Local variables
    BNode<type>* tmpL;
    BNode<type>* tmpR;
    type childMidKey;
    int midKeyinsertIndex;

    // ## split child into 2 nodes ##
    // 1. Create the 2 nodes
    tmpL = new BNode<type>();
    tmpR = new BNode<type>();
    tmpL->setLeaf(child->isLeaf());
    tmpR->setLeaf(child->isLeaf());

    cout << "created new nodes" << endl;

    // 2. Populate the 2 nodes with keys
    for (int i = 0; i < child->getKeyNo(); i++){
        if (i < splitIndex){
            tmpL->addKey(child->getKey(i), tmpL->getKeyNo());
        } else if ( i == splitIndex){
            childMidKey =child->getKey(i);
        } else {
            tmpR->addKey(child->getKey(i), tmpR->getKeyNo());
        }
    }

    cout << "populated with keys" << endl;

    // 3. Populate the 2 nodes with children
    for (int i = 0; i < child->getChildNo(); i++){
        if (i <= splitIndex){
            tmpL->addChild(child->getChild(i), tmpL->getChildNo());
        } else {
            tmpR->addChild(child->getChild(i), tmpR->getChildNo());
        }
    }

    // 4.a. Insert the middle key of child to parent if not null
    if (parent){
        for (int i = 0; i < parent->getKeyNo(); i++){
            if (childMidKey < parent->getKey(i)){
                // insert at i so stays before the one greater than it
                parent->addKey(childMidKey, i);
                midKeyinsertIndex = i;
            } else if ( i == parent->getKeyNo() - 1) {
                // not less than the last node, insert at the end
                parent->addKey(childMidKey, i + 1);
                midKeyinsertIndex = i + 1;
                break;
            }
        }
    } 
    // 4.b. If parent is null, make a new parent and insert child middle key into it
    else {
        cout << "creating a new parent " << endl;
        parent = new BNode<type>();
        parent->setLeaf(false);
        parent->addKey(childMidKey, 0);
        midKeyinsertIndex = 0;
        // No worries here, old root is kept by child here and this case won't happen
        // anywhere other than at the root
        this->root = parent;
    }

    cout << "removing the child from parent" << endl;
    // 5. Remove the old child from parent and delete it
    parent->removeChild(child);

    cout << "removed the child from parent" << endl;

    // 6. Insert the two new nodes to parent
    parent->addChild(tmpL, midKeyinsertIndex);
    parent->addChild(tmpR, midKeyinsertIndex + 1);
}

/**
 * Traverses the whole tree and prints it out
 * @param curNode The node being processed
 * @param level The level at which is the node
 * */
template <class type>
void BTree<type>::traverse(BNode<type>* curNode, int level){
    // Base case - NULL return
    if (!curNode){
        return;
    }

    // print self
    for(int i = 0; i < level; i ++){
        cout << "\t";
    }
    for (int i = 0; i < curNode->getKeyNo(); i++){
        cout << curNode->getKey(i) << " , " ;
    }
    cout << endl;

    // print children
    for (int i = 0; i < curNode->getChildNo(); i++){
        traverse(curNode->getChild(i), level + 1);
    }
}

/**
 * Recursive remove method
 * @param key The key to be removed
 * @param curNode The current node being processed
 * @param parentNode The parent of the current node
 * */
template <class type>
void BTree<type>::remove(type key, BNode<type>* curNode, BNode<type>* parentNode){
    cout << "recursive remove" << endl;
    // Local variables
    BNode<type>* curNodeRight = NULL;
    BNode<type>* curNodeLeft = NULL;
    type inorderReplacementKey;
    bool couldGive = false;

    // Base case - Leaf node -
    if (curNode->isLeaf()){
        cout << "at leaf" << endl;
        for (int i = 0; i < curNode->getKeyNo(); i++){
            if (curNode->getKey(i) == key){
                // The key found.. delete it
                curNode->removeKey(i);

                // Now tree might lost balance, so balance it
                balance(curNode, parentNode);
            }
        }

        return;
    }

    // Not a leaf node
    // Check if key is there to delete it
    for (int i = 0; i < curNode->getKeyNo(); i++){
        if (curNode->getKey(i) == key){
            // ## NOTE : Can't delete it directly, so replace with inorder successor or predecessor

            // Finding the direct left and right children around key in question
            curNodeLeft = curNode->getChild(i);
            curNodeRight = curNode->getChild(i + 1);

            if (prioritizeInorderPredecessor){
                couldGive = findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, false);
            }
            
            // if first try was not successful or the priority whas for successor
            // , try with successor
            if (!prioritizeInorderPredecessor || !couldGive){
                couldGive = findInorderSuccessor(key, inorderReplacementKey, curNodeRight, false);
            }

            if (!prioritizeInorderPredecessor && !couldGive){
                couldGive = findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, false);
            }

            // if again could not give, take from the side of the first try anyway
            if (!couldGive){
                if (prioritizeInorderPredecessor){
                    couldGive = findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, true);
                } else {
                    couldGive = findInorderSuccessor(key, inorderReplacementKey, curNodeRight, true);
                }
            }

            cout << "got replacement " << inorderReplacementKey << endl;

            // Now a replacement is obtained, so replace key in current node with it
            curNode->removeKey(i);
            curNode->addKey(inorderReplacementKey, i);

            // Replace they key to be deleted with the replacement key
            // so they algorithm keeps going till the bottom of the tree
            // to delete it and balance tree in the way back
            key = inorderReplacementKey;
        }
    }

    // continue with the child that will contain the key
    for (int i = 0; i < curNode->getKeyNo(); i++) {
        if (key < curNode->getKey(i)) {
            // continue with the tree just before the key greater than it
            remove(key, curNode->getChild(i), curNode);
        }
        else if (i == curNode->getKeyNo() - 1) {
            // Greater than the last key
            remove(key, curNode->getChild(i+1), curNode);
            break;
        }
    }

    // in the way back
    // balance might have been disrupted so check balance
    balance(curNode, parentNode);
}

template <class type>
bool BTree<type>::rotate(BNode<type>* child, BNode<type>* parent){
    cout << "performing rotation" << endl;
    // Local variables
    BNode<type>* sbling = NULL;
    BNode<type>* rightSbling = NULL;
    BNode<type>* leftSbling = NULL;
    bool rotateSuccessful = false;
    bool rightSblingCanDonate = false;
    bool leftSblingCanDonate = false;

    // The code

    // Find the right and left sblings
    for (int i = 0; i < parent->getChildNo() - 1; i++){
        if (parent->getChild(i) == child)
            rightSbling = parent->getChild(i+1);
        if (parent->getChild(i+1) == child)
            leftSbling = parent->getChild(i);
    }

    leftSbling && leftSbling->getKeyNo() > this->minNumKeys 
    ? leftSblingCanDonate = true 
    : leftSblingCanDonate = false;

    rightSbling && rightSbling->getKeyNo() > this->minNumKeys 
    ? rightSblingCanDonate = true 
    : rightSblingCanDonate = false;

    // Try rotating left
    if (
        (this->prioritizeRotatingLeft || !leftSblingCanDonate) 
        && rightSbling 
        && rightSbling->getKeyNo() > this->minNumKeys
        ){
        rotateSuccessful = rotateL(child, rightSbling, parent);
    } 
    
    // or try rotating right
    if ((!this->prioritizeRotatingLeft || !rightSblingCanDonate)
        && leftSbling 
        && leftSbling->getKeyNo() > this->minNumKeys
        ){  
            cout << "min key nums : " << this->minNumKeys << endl;
            cout << "parent kids : " << endl;
            for ( int i = 0; i < parent->getChildNo(); i++)
                cout << parent->getChild(i) << "  ";
            cout << "\n left sblinbg and child " << leftSbling << " " << child << endl;
        rotateSuccessful = rotateR(leftSbling, child, parent);
    }

    return rotateSuccessful;
}

template <class type>
bool BTree<type>::rotateL(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent){
    cout << "rotating left" << endl;
    // Local variables
    int keyIndex;

    // 1. Move key between the children from parent to child in need (Left child)
    // Find the index of the key
    for (int i = 0; i < parent->getChildNo(); i++)
        if (parent->getChild(i) == childL)
            keyIndex = i;
    // Add the key to the child
    childL->addKey(parent->getKey(keyIndex), childL->getKeyNo());

    // 2.a. Move first key from child donating (right child) to parent at same
    // location of key moved to left child
    parent->removeKey(keyIndex);
    parent->addKey(childR->getKey(0), keyIndex);
    // 2.b. remove the first key from right child
    childR->removeKey(0);

    // 3. move first child of right child to be last of left child
    if (childR->getChildNo() > 0){
        childL->addChild(childR->getChild(0), childL->getChildNo());
        childR->removeChild(childR->getChild(0));
    }

    return true;
}

template <class type>
bool BTree<type>::rotateR(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent){
    cout << "rotating right" << endl;
    // Local variable 
    int keyIndex;

    // 1. Move key between the children.. from parent to child in need (right child)
    // Find the index of the key
    for (int i = 0; i < parent->getChildNo(); i++)
        if (parent->getChild(i) == childL)
            keyIndex = i;

    cout << "keyIndex : " << keyIndex << endl;
    // Add the key to the child
    childR->addKey(parent->getKey(keyIndex), 0);

    cout << "key added to right child" << endl;

    // 2.a. Move first key from child donating (left child) to parent at same
    // location of key moved to left child
    parent->removeKey(keyIndex);
    parent->addKey(childL->getKey(childL->getKeyNo() - 1), keyIndex);
    // 2.b. remove the first key from right child
    childL->removeKey(childL->getKeyNo() - 1);

    cout << "key added to parent" << endl;

    // 3. move last child of left child to be first of right child
    if (childL->getChildNo() > 0){
        childR->addChild(childL->getChild(childL->getChildNo() - 1), 0);
        childL->removeChild(childL->getChild(childL->getChildNo() - 1));
    }

    cout << "rotating right finidhed without problems" << endl;

    return true;
}

template <class type>
void BTree<type>::merge(BNode<type>* child, BNode<type>* parent){
    cout << "at merge" << endl;
    // Local variables
    BNode<type>* leftSbling = NULL;
    BNode<type>* rightSbling = NULL;
    BNode<type>* tmpMergedNode = NULL;
    int leftSblingIndex;

    // Get the left and right sblings
    for (int i = 0; i < parent->getChildNo(); i++){
        if (parent->getChild(i) == child){
            leftSblingIndex = i;

            if (i > 0)
                leftSbling = parent->getChild(i-1);
            if (i < parent->getChildNo() - 1)
                rightSbling = parent->getChild(i+1);
        }
    }

    // Set up the variables
    // Merge with right if available and is prioritized or left is unavailable
    if ((prioritizeRotatingLeft || !leftSbling) && rightSbling){
        cout << "setting left sbling to child" << endl;
        leftSbling = child;
    }
    // Merge with left if available and is prioritized or right 
    else if ((!prioritizeRotatingLeft || !rightSbling) && leftSbling){
        cout << "setting right sbling to child" << endl;
        leftSblingIndex --;
        rightSbling = child;
    }

    // Perform the logic
    // Merge with left or right sbling according to availability and priority
    tmpMergedNode = new BNode<type>();
    
    // Add keys from child 1
    for (int i = 0; i < leftSbling->getKeyNo(); i++)
        tmpMergedNode->addKey(leftSbling->getKey(i), tmpMergedNode->getKeyNo());
    cout << "keys added from child 1" << endl;

    // Add the middle key from parent btwn child 1 and 2 and remove it
    cout << "left sbling index : " << leftSblingIndex << "  self : " << parent->getKey(leftSblingIndex) << endl;
    tmpMergedNode->addKey(parent->getKey(leftSblingIndex), tmpMergedNode->getKeyNo());
    parent->removeKey(leftSblingIndex);
    cout << "keys added from parent" << endl;

    // Add keys from child 2
    for (int i = 0; i < rightSbling->getKeyNo(); i++)
        tmpMergedNode->addKey(rightSbling->getKey(i), tmpMergedNode->getKeyNo());
    cout << "keys added from child 2" << endl;

    // Add children from child 1 and 2
    if (leftSbling->getChildNo() > 0){
        for (int i = 0; i < leftSbling->getChildNo(); i++)
            tmpMergedNode->addChild(leftSbling->getChild(i), tmpMergedNode->getChildNo());
    }
    if (rightSbling->getChildNo() > 0){
        for (int i = 0; i < rightSbling->getChildNo(); i++)
            tmpMergedNode->addChild(rightSbling->getChild(i), tmpMergedNode->getChildNo());
    }

    // Setting the new node state
    tmpMergedNode->setLeaf(leftSbling->isLeaf());
    
    // Remove child and left sbling from parent
    parent->removeChild(leftSbling);
    parent->removeChild(rightSbling);

    // attach the new node instead of them
    parent->addChild(tmpMergedNode, leftSblingIndex);

}

template <class type>
bool BTree<type>::findInorderSuccessor(type key, type &successorKey, BNode<type>* curNode, bool forceExtraction){
    cout << "finding inorder successor with node : " << curNode << endl;
    // Base case - reached a leaf node
    if (curNode->isLeaf()){
        cout << "is leaf" << endl;
        // check if it cannot donate, return
        if (!forceExtraction && curNode->getKeyNo() <= this->minNumKeys)
            return false;

        // Get it no matter what
        successorKey = curNode->getKey(0);
        return true;
    }
    
    // Go to most left child
    findInorderSuccessor(key, successorKey, curNode->getChild(0), forceExtraction);
}

template <class type>
bool BTree<type>::findInorderPredecessor(type key, type &predecessorKey, BNode<type>* curNode, bool forceExtraction){
    cout << "finding inorder predecessor " << endl;
    // Base case - reached a leaf node
    if (curNode->isLeaf()){
        // check if it cannot donate, return
        if (!forceExtraction && curNode->getKeyNo() <= this->minNumKeys)
            return false;

        // Get it no matter what
        predecessorKey = curNode->getKey(curNode->getKeyNo() - 1);
        return true;
    }
    
    // Go to most right child
    findInorderSuccessor(key, predecessorKey, curNode->getChild(curNode->getChildNo() - 1), forceExtraction);
}

template <class type>
bool BTree<type>::isValidBTreeString(string bTreeString){

}


template <class type>// TreeViz specific functions
void BTree<type>::toTreeString(BNode<type>* curNode, string &output){
    std::ostringstream oss;

    // Base Case
    if (curNode->isLeaf()){
        // wrap its contents with {}
        oss << "{";

        if (curNode->getKeyNo() > 0){
            oss << curNode->getKey(0);
            for (int i = 1; i < curNode->getKeyNo(); i++){
                oss << "," << curNode->getKey(i);
            }
        }

        oss << "}";
        output += oss.str();
        oss.str("");
        oss.clear();
        return;
    }

    // Not a leaf
    // *** add self ***
    oss << "{";

    if (curNode->getKeyNo() > 0){
        oss << curNode->getKey(0);
        for (int i = 1; i < curNode->getKeyNo(); i++){
            oss << "," << curNode->getKey(i);
        }
    }

    oss << "}";
    output += oss.str();
    oss.str("");
    oss.clear();

    // add children
    if (curNode->getChildNo() > 0){
        oss << "(";
        output += oss.str();
        oss.str("");
        oss.clear();

        toTreeString(curNode->getChild(0), output);

        for (int i = 1; i < curNode->getChildNo(); i++){
            oss << ",";
            output += oss.str();
            oss.str("");
            oss.clear();

            toTreeString(curNode->getChild(i), output);
        }

        oss << ")";
        output += oss.str();
        oss.str("");
        oss.clear();
    }
}

template <class type>
void BTree<type>::insert(BNode<type>* child, BNode<type>* parent){
    cout << "at insert" << endl;

    if (parent == NULL){
        cout << "a new root " << child << endl;
        root = child;
        return;
    }

    cout << "adding a child " << child << " to parent " << parent << endl;
    parent->addChild(child, parent->getChildNo());
}


// template class BTree<int>;


int main(){
    // BNode<int>* node1 = new BNode<int>();
    // BNode<int>* node2 = new BNode<int>();
    // BNode<int>* node3 = new BNode<int>();
    // BNode<int>* node4 = new BNode<int>();
    // BNode<int>* node5 = new BNode<int>();

    // node1->addKey(1, 0);
    // node1->addKey(2, 0);
    // node1->addKey(3, 0);
    // node1->addKey(4, 0);

    // node2->addKey(22, 0);
    // node3->addKey(33, 0);
    // node4->addKey(44, 0);


    // cout << node1->getKey(0) << endl;
    // cout << node1->getKey(1) << endl;
    // cout << node1->getKey(2) << endl;
    // cout << node1->getKey(3) << endl;

    // // node1->addChild(node2, 0);
    // // node1->addChild(node3, 0);
    // // node1->addChild(node4, 1);
    // // node1->removeChild(node3);

    // cout << node1->getChild(0)->getKey(0) << endl;
    // cout << node1->getChild(1)->getKey(0) << endl;
    // // cout << node1->getChild(2)->getKey(0) << endl;

    BTree<int>* tree1 = new BTree<int>(70);
    for (int i = 0; i < 1700 ; i++){
        tree1->insert(i);  
    }

    // tree1->constructFromTreeString("{5,8,12}({3}({1}{4}),{6}({5}{7}),{10}({9}{11}),{14}({13}{15}))");

    cout << "before" << endl;
    tree1->traverse();

    cout << endl;
    cout << tree1->toTreeString() << endl;
    // tree1->remove(15);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    // tree1->remove(2);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    // tree1->remove(8);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    // tree1->remove(1);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(3);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(4);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    // tree1->remove(5);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(6);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(7);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(9);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //         tree1->remove(10);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //         tree1->remove(11);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(12);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //     tree1->remove(13);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    //         tree1->remove(14);
    // // tree1->insert(15);

    // cout << "after" << endl;
    // tree1->traverse();

    return 0;
}