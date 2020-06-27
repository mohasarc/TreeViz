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
    this->sequence = "";
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
    // Local variables
    bool success = false;
    if (this->root == NULL){
        // cout << "creating root" << endl;
        this->root = new BNode<type>();
        this->root->setLeaf(true);
    }
    
    // add key to the tree
    this->insert(key, this->root, NULL, success);

    if (success){
        // add key to the sequence
        if (this->sequence.size() > 0)
            sequence += "," + keyToString(key);
        else
            sequence += keyToString(key);
    }
}

/**
 * @param key The key to be removed
 * */
template <class type>
void BTree<type>::remove(type key){
    // Local variables
    bool success = false;

    // If empty don't remove
    if (!this->root)
        return;

    remove(key, this->root, NULL, success);

    if (success)
        this->sequence += ",d" + keyToString(key);
}

/**
 * @param key The key to be found
 * */
template <class type>
bool BTree<type>::find(type key){
    return false;
}

/**
 * Traverses the whole tree
 * */
template <class type>
void BTree<type>::traverse(){
    this->traverse(this->root, 0);
}

template <class type>
void BTree<type>::setOrder(int order){
    this->degree = order;
}

template <class type>
int BTree<type>::getOrder(){
    return this->degree;
}

template <class type>
void BTree<type>::setPropagateS(bool propagateS){
    this->propagateS = propagateS;
}

template <class type>
bool BTree<type>::getPropagateS(){
    return this->propagateS;
}

template <class type>
void BTree<type>::setPrioritizeInorderPredecessor(bool prioritizeInorderPredecessor){
    this->prioritizeInorderPredecessor = prioritizeInorderPredecessor;
}

template <class type>
bool BTree<type>::getPrioritizeInorderPredecessor(){
    return this->prioritizeInorderPredecessor;
}

template <class type>
void BTree<type>::setPrioritizeRotateLeft(bool prioritizeRotatingLeft){
    this->prioritizeRotatingLeft = prioritizeRotatingLeft;
}

template <class type>
bool BTree<type>::getPrioritizeRotateLeft(){
    return this->prioritizeRotatingLeft;
}


/**
 * 
 * */
template <class type>
string BTree<type>::toTreeString(){
    string output = "";
    if (this->root)
        toTreeString(this->root, output);

    return output;
}

template <class type>
bool BTree<type>::insertSequence(string sequence){
    // Check if a valid number sequence
    static CRegexpT <char> regexp(R"(\d(,?d?-?(?R))*)");
    // test
    MatchResult result = regexp.MatchExact(sequence.c_str());
    // matched or not
    if (result.IsMatched()){
        // Get all numbers as strings
        istringstream ss( sequence );
        vector <string> record;
        while (ss)
        {
        string tmpNumStr;
        if (!getline( ss, tmpNumStr, ',' )) break;
        record.push_back( tmpNumStr );
        }

        // THERE CAN BE MULTIPLE DELETIONS / INSERTIONS
        // // Make sure that there are no repetitions
        // for (int i = 0; i < record.size(); i++){
        //     for (int j = i + 1; j < record.size(); j++){
        //         if (record[i] == record[j])
        //             return false;
        //     }
        // }

        // Parse all string numbers as integers and add them to the tree
        for (string numStr : record){
            if (numStr.at(0) == 'd')
                remove(stoi(numStr.substr(1)));
            else
                insert(stoi(numStr));
        }

        return true;
    }

    return false;
}

template <class type>
void BTree<type>::setSequence(string sequence){
    this->sequence = sequence;
}

template <class type>
string BTree<type>::getSequence(){
    return this->sequence;
}

template <class type>
string BTree<type>::generateInorderSequence(){
    string inorderSequence = "";
    this->generateInorderSequence(this->root, inorderSequence);
    return inorderSequence;
}


/**
 * Builds the tree out of a tree string
 * @param treeString The treeString describig the tree
 * */
template <class type>
bool BTree<type>::constructFromTreeString(string treeString){
    // cout << "at construct" << endl;
    stack<BNode<type>*> parentsStack;
    BNode<type>* tmpNode;
    int childCount = 0;

    // Validate the tree string
    if (!isValidBTreeString(treeString)){
        // if not valid
        return false;
    }

    for (int i = 0; i < treeString.length(); i++){
        // cout << "at char " << treeString.at(i) << endl;
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

    return true;
}

template <class type>
vector<Step> BTree<type>::getSteps(){
    return this->steps;
}

template <class type>
int BTree<type>::getStepsNo(){
    return this->steps.size();
}

template <class type>
string BTree<type>::getStepText(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].text;
    return "";
}

template <class type>
string BTree<type>::getStepTreeStr(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].treeStr;
    return "";
}

template <class type>
string BTree<type>::getStepNote(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].note;
    return "";
}

template <class type>
void BTree<type>::clearSteps(){
    this->steps.clear();
}

// Private functions implementations
/**
 * 
 * */
template <class type>
void BTree<type>::insert(type key, BNode<type>* curNode, BNode<type>* parentNode, bool &success){
    // Local variables
    string note = "inserting: " + keyToString(key);
    string stepText;

    // cout << "in recursive insert" << endl;
    // Base case
    // -- If leaf insert at it --
    if (curNode->isLeaf()){
        if (curNode->getKeyNo() > 0){
            // Record a step
            curNode->setColor("select");
            recordStep("Reached a leaf node, insert the key at it", note);
            curNode->setColor("");
        }

        // cout << "it is leaf & trying to insert " << key << endl;
        for (int i = 0; i < curNode->getKeyNo(); i++) {
            if (key < curNode->getKey(i)) {
                // insert at it
                curNode->addKey(key, i);
                success = true;
                break;
            } else if ( i ==  curNode->getKeyNo() - 1) {
                // insert at it
                // cout << "inserting " << key << " at " << i+1 << endl;
                curNode->addKey(key, i + 1);
                success = true;
                break;
            }
        }

        if (curNode->getKeyNo() == 0){
            curNode->addKey(key, 0);
            success = true;
        }

        BNode<type>* parentBeforeSplit = parentNode; // For capturing step
        // May become unbalanced so check balance
        this->balance(curNode, parentNode);

        // If curNode is still part of the tree, it is the place where insertion happened
        if (parentNode != NULL){
            for (int i = 0; i < parentNode->getChildNo(); i++){
                if (parentNode->getChild(i) == curNode){ 
                    curNode->setColor("success");
                    recordStep("Key inserted successfully", note);
                    curNode->setColor("");
                }
            }
        } else if (curNode == this->root) {
            curNode->setColor("success");
            recordStep("Key inserted successfully", note);
            curNode->setColor("");
        }

        return;
    }
    
    // cout << "not a leaf" << endl;

    // Not leaf
    // Record a step
    curNode->setColor("select");
    recordStep("Finding a direction to go to", note);
    curNode->setColor("");
    // Go through current node's children and decide to 
    // which one to go
    for (int i = 0; i < curNode->getKeyNo(); i++) {
        if (key < curNode->getKey(i)) {
            // insert in the tree just before the key greater than it
            insert(key, curNode->getChild(i), curNode, success);
            break;
        }
        else if (i == curNode->getKeyNo() - 1) {
            // Greater than the last key
            insert(key, curNode->getChild(i+1), curNode, success);
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
void BTree<type>::balance(BNode<type>* child, BNode<type>* &parent){
    // Local variables
    int splitIndex = 0;
    int childKeyNo = child->getKeyNo();
    bool rotateSuccessful = false;

    // cout << "at balance with " << childKeyNo << " keys " << endl;

    // if the child has more than or equal to degree number of keys it is not balanced
    // (overFull)
    if (childKeyNo > this->degree - 1){
        // Record a step
        child->setColor("alert");
        recordStep("The node is over-full, perform a split", "");
        child->setColor("");

        // cout << "not balanced" << endl;
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
        // child->setColor("");

        // cout << "under-full" << endl;
        if (parent){
            child->setColor("alert");
            recordStep("The node is under-full", "");
            // Sol 1. Try borrowing from left or right sbling
            rotateSuccessful = rotate(child, parent);

            // Sol 2. Perform a merge
            if (!rotateSuccessful){
                child->setColor("alert");
                recordStep("Both sblings cannot donate: perform a merge", "");
                child->setColor("");

                merge(child, parent);
            }
        }
        // Parent is null means child is the root
        else {
            // cout << "parent is null at root" << endl;
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
    // cout << "at split with split index " << splitIndex << endl;
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

    // cout << "created new nodes" << endl;

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

    // 2.b remove the middle key from the child
    child->removeKey(splitIndex);

    // cout << "populated with keys" << endl;

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
                break;
            } else if ( i == parent->getKeyNo() - 1) {
                // not less than the last node, insert at the end
                parent->addKey(childMidKey, i + 1);
                midKeyinsertIndex = i + 1;
                break;
            }
        }

        // Record a step
        parent->setColor("alert");
        child->setColor("alert");
        recordStep("Push middle key up to parent", "");
        parent->setColor("");
        child->setColor("");
    } 
    // 4.b. If parent is null, make a new parent and insert child middle key into it
    else {
        // cout << "creating a new parent " << endl;
        parent = new BNode<type>();
        parent->setLeaf(false);
        parent->addKey(childMidKey, 0);
        midKeyinsertIndex = 0;
        // No worries here, old root is kept by child here and this case won't happen
        // anywhere other than at the root
        this->root = parent;

        parent->addChild(child, 0); // For the record not to fail

        // Record a step
        parent->setColor("alert");
        child->setColor("alert");
        recordStep("No parent, create one and push middle key to it", "");
        parent->setColor("");
        child->setColor("");
    }

    // cout << "removing the child from parent" << endl;
    // 5. Remove the old child from parent and delete it
    parent->removeChild(child);

    // cout << "removed the child from parent" << endl;

    // 6. Insert the two new nodes to parent
    parent->addChild(tmpL, midKeyinsertIndex);
    parent->addChild(tmpR, midKeyinsertIndex + 1);

    // Record a step
    parent->setColor("success");
    tmpL->setColor("success");
    tmpR->setColor("success");
    recordStep("Split the child into two nodes", "");
    parent->setColor("");
    tmpL->setColor("");
    tmpR->setColor("");
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
void BTree<type>::remove(type key, BNode<type>* curNode, BNode<type>* parentNode, bool &success){
    // cout << "recursive remove" << endl;
    // Local variables
    BNode<type>* curNodeRight = NULL;
    BNode<type>* curNodeLeft = NULL;
    type inorderReplacementKey;
    bool couldGive = false;
    bool replacedWithInorderPredecessor = false;
    string note = "removing: " + keyToString(key);

    // Base case - Leaf node -
    if (curNode->isLeaf()){
        // cout << "at leaf" << endl;
        for (int i = 0; i < curNode->getKeyNo(); i++){
            if (curNode->getKey(i) == key){
                curNode->setColor("select");
                recordStep("", note);
                curNode->setColor("danger");
                recordStep("The key found at a leaf node: just delete it", note);
                curNode->setColor("");

                // The key found.. delete it
                curNode->removeKey(i);

                // feedback
                success = true;

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
            curNode->setColor("select");
            recordStep("", note);
            curNode->setColor("danger");
            recordStep("The key found at a non-leaf node: replace with inorder successor or predecessor", note);

            // Finding the direct left and right children around key in question
            curNodeLeft = curNode->getChild(i);
            curNodeRight = curNode->getChild(i + 1);

            if (prioritizeInorderPredecessor){
                findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, false, couldGive);
                if (couldGive){
                    replacedWithInorderPredecessor = true;
                    curNodeLeft->setColor("alert");
                    recordStep("replacing with inorder predecessor", note);
                }
            }
            
            // if first try was not successful or the priority whas for successor
            // , try with successor
            if (!prioritizeInorderPredecessor || !couldGive){
                findInorderSuccessor(key, inorderReplacementKey, curNodeRight, false, couldGive);
                if (couldGive){
                    curNodeRight->setColor("alert");
                    recordStep("replacing with inorder successor", note);
                }
            }

            if (!prioritizeInorderPredecessor && !couldGive){
                findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, false, couldGive);
                if (couldGive){
                    replacedWithInorderPredecessor = true;
                    curNodeLeft->setColor("alert");
                    recordStep("replacing with inorder predecessor", note);
                }
            }

            // if again could not give, take from the side of the first try anyway
            if (!couldGive){
                if (prioritizeInorderPredecessor){
                    findInorderPredecessor(key, inorderReplacementKey, curNodeLeft, true, couldGive);
                    if (couldGive){
                        replacedWithInorderPredecessor = true;
                        curNodeLeft->setColor("alert");
                        recordStep("replacing with inorder predecessor", note);
                    }
                } else {
                    findInorderSuccessor(key, inorderReplacementKey, curNodeRight, true, couldGive);
                    if (couldGive){
                        curNodeRight->setColor("alert");
                        recordStep("replacing with inorder successor", note);
                    }
                }
            }

            // cout << "got replacement " << inorderReplacementKey << endl;

            // Now a replacement is obtained, so replace key in current node with it
            curNode->removeKey(i);
            curNode->addKey(inorderReplacementKey, i);

            // curNode->setColor("");
            recordStep("Now delete the replacement key", note);

            // feedback
            success = true;

            // Replace they key to be deleted with the replacement key
            // so they algorithm keeps going till the bottom of the tree
            // to delete it and balance tree in the way back
            key = inorderReplacementKey;
        }
    }

    // continue with the child that will contain the key
    for (int i = 0; i < curNode->getKeyNo(); i++) {
        if (key < curNode->getKey(i)) {
            curNode->setColor("select");
            recordStep("searching for the key to be deleted", note);
            curNode->setColor("");

            // continue with the tree just before the key greater than it
            remove(key, curNode->getChild(i), curNode, success);
            break;
        } 
        // To fix the problem of the key being == to key in this node after replacement
        else if (key == curNode->getKey(i) && replacedWithInorderPredecessor){
            curNode->setColor("select");
            recordStep("searching for the key to be deleted", note);
            curNode->setColor("");

            remove(key, curNode->getChild(i), curNode, success);
            break;
        }
        else if (i == curNode->getKeyNo() - 1) {
            curNode->setColor("select");
            recordStep("searching for the key to be deleted", note);
            curNode->setColor("");

            // Greater than the last key
            remove(key, curNode->getChild(i+1), curNode, success);
            break;
        }
    }

    // in the way back
    // balance might have been disrupted so check balance
    balance(curNode, parentNode);
}

template <class type>
bool BTree<type>::rotate(BNode<type>* child, BNode<type>* parent){
    // cout << "performing rotation" << endl;
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

        rightSbling->setColor("alert");
        recordStep("Right sbling can donate", "");
        rightSbling->setColor("");

        rotateSuccessful = rotateL(child, rightSbling, parent);
    } 
    
    // or try rotating right
    if ((!this->prioritizeRotatingLeft || !rightSblingCanDonate)
        && leftSbling 
        && leftSbling->getKeyNo() > this->minNumKeys
        ){  
            // cout << "min key nums : " << this->minNumKeys << endl;
            // cout << "parent kids : " << endl;
            // for ( int i = 0; i < parent->getChildNo(); i++)
                // cout << parent->getChild(i) << "  ";
            // cout << "\n left sblinbg and child " << leftSbling << " " << child << endl;
            leftSbling->setColor("alert");
            recordStep("Left sbling can donate", "");
            leftSbling->setColor("");

        rotateSuccessful = rotateR(leftSbling, child, parent);
    }

    return rotateSuccessful;
}

template <class type>
bool BTree<type>::rotateL(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent){
    // // cout << "rotating left" << endl;
    // Local variables
    int keyIndex;

    // 1. Move key between the children from parent to child in need (Left child)
    // Find the index of the key
    for (int i = 0; i < parent->getChildNo(); i++)
        if (parent->getChild(i) == childL)
            keyIndex = i;
    
    parent->setColor("alert");
    childL->setColor("alert");
    recordStep("Move key from parent to child in need", "");

    // Add the key to the child
    childL->addKey(parent->getKey(keyIndex), childL->getKeyNo());
    parent->removeKey(keyIndex);

    recordStep("", "");
    parent->setColor("");
    childL->setColor("");

    parent->setColor("alert");
    childR->setColor("alert");
    recordStep("Move key from child donating to parent", "");

    // 2.a. Move first key from child donating (right child) to parent at same
    // location of key moved to left child
    parent->addKey(childR->getKey(0), keyIndex);
    // 2.b. remove the first key from right child
    childR->removeKey(0);

    recordStep("", "");
    parent->setColor("");
    childR->setColor("");

    // 3. move first child of right child to be last of left child
    if (childR->getChildNo() > 0){
        childR->getChild(0)->setColor("alert");
        recordStep("Move the most left subtree of the right child to the left one", "");

        childL->addChild(childR->getChild(0), childL->getChildNo());
        childR->removeChild(childR->getChild(0));

        recordStep("", "");
        childL->getChild(childL->getChildNo() - 1)->setColor("");
    }

    return true;
}

template <class type>
bool BTree<type>::rotateR(BNode<type>* childL, BNode<type>* childR, BNode<type>* parent){
    // cout << "rotating right" << endl;
    // Local variable 
    int keyIndex;

    // 1. Move key between the children.. from parent to child in need (right child)
    // Find the index of the key
    for (int i = 0; i < parent->getChildNo(); i++)
        if (parent->getChild(i) == childL)
            keyIndex = i;

    // cout << "keyIndex : " << keyIndex << endl;
    parent->setColor("alert");
    childR->setColor("alert");
    recordStep("Move key from parent to child in need", "");

    // Add the key to the child
    childR->addKey(parent->getKey(keyIndex), 0);
    parent->removeKey(keyIndex);

    recordStep("", "");
    parent->setColor("");
    childR->setColor("");

    parent->setColor("alert");
    childL->setColor("alert");
    recordStep("Move key from child donating to parent", "");

    // cout << "key added to right child" << endl;

    // 2.a. Move first key from child donating (left child) to parent at same
    // location of key moved to left child
    parent->addKey(childL->getKey(childL->getKeyNo() - 1), keyIndex);
    // 2.b. remove the first key from right child
    childL->removeKey(childL->getKeyNo() - 1);

    // cout << "key added to parent" << endl;
    recordStep("", "");
    parent->setColor("");
    childL->setColor("");

    // 3. move last child of left child to be first of right child
    if (childL->getChildNo() > 0){
        childL->getChild(childL->getChildNo() - 1)->setColor("alert");
        recordStep("Move the most right subtree of the left child to the right one", "");

        childR->addChild(childL->getChild(childL->getChildNo() - 1), 0);
        childL->removeChild(childL->getChild(childL->getChildNo() - 1));

        recordStep("", "");
        childR->getChild(0)->setColor("");
    }

    // cout << "rotating right finidhed without problems" << endl;

    return true;
}

template <class type>
void BTree<type>::merge(BNode<type>* child, BNode<type>* parent){
    // cout << "at merge" << endl;
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
        // cout << "setting left sbling to child" << endl;
        leftSbling = child;
    }
    // Merge with left if available and is prioritized or right 
    else if ((!prioritizeRotatingLeft || !rightSbling) && leftSbling){
        // cout << "setting right sbling to child" << endl;
        leftSblingIndex --;
        rightSbling = child;
    }

    // Perform the logic
    // Merge with left or right sbling according to availability and priority
    tmpMergedNode = new BNode<type>();

    parent->setColor("alert");
    leftSbling->setColor("alert");
    rightSbling->setColor("alert");
    recordStep("", "");

    // Add keys from child 1
    for (int i = 0; i < leftSbling->getKeyNo(); i++)
        tmpMergedNode->addKey(leftSbling->getKey(i), tmpMergedNode->getKeyNo());
    // cout << "keys added from child 1" << endl;

    // Add the middle key from parent btwn child 1 and 2 and remove it
    // cout << "left sbling index : " << leftSblingIndex << "  self : " << parent->getKey(leftSblingIndex) << endl;
    tmpMergedNode->addKey(parent->getKey(leftSblingIndex), tmpMergedNode->getKeyNo());
    type parentMiddleKey = parent->getKey(leftSblingIndex);
    parent->removeKey(leftSblingIndex);
    // cout << "keys added from parent" << endl;

    // Add keys from child 2
    for (int i = 0; i < rightSbling->getKeyNo(); i++)
        tmpMergedNode->addKey(rightSbling->getKey(i), tmpMergedNode->getKeyNo());
    // cout << "keys added from child 2" << endl;

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
    
    child->addKey(parentMiddleKey, 0); // only for graphics
    recordStep("Push middle key down and merge it with the two children", "");

    // Remove child and left sbling from parent
    parent->removeChild(leftSbling);
    parent->removeChild(rightSbling);

    // attach the new node instead of them
    parent->addChild(tmpMergedNode, leftSblingIndex);

    tmpMergedNode->setColor("alert");
    recordStep("", "");
    parent->setColor("");
    tmpMergedNode->setColor("");
}

template <class type>
void BTree<type>::findInorderSuccessor(type key, type &successorKey, BNode<type>* &curNode, bool forceExtraction, bool &success){
    // cout << "finding inorder successor with node : " << curNode << endl;
    // Base case - reached a leaf node
    if (curNode->isLeaf()){
        // cout << "is leaf" << endl;
        // check if it cannot donate, return
        if (!forceExtraction && curNode->getKeyNo() <= this->minNumKeys){
            success = false;
            return;
        }

        // Get it no matter what
        successorKey = curNode->getKey(0);
        success = true;
        return;
    }
    
    curNode = curNode->getChild(0);
    // Go to most left child
    findInorderSuccessor(key, successorKey, curNode, forceExtraction, success);
}

template <class type>
void BTree<type>::findInorderPredecessor(type key, type &predecessorKey, BNode<type>* &curNode, bool forceExtraction, bool &success){
    // cout << "finding inorder predecessor " << endl;
    // Base case - reached a leaf node
    if (curNode->isLeaf()){
        // check if it cannot donate, return
        if (!forceExtraction && curNode->getKeyNo() <= this->minNumKeys){
            success = false;
            return;
        }

        // Get it no matter what
        predecessorKey = curNode->getKey(curNode->getKeyNo() - 1);
        success = true;
        return;
    }
    
    // Go to most right child
    curNode = curNode->getChild(curNode->getChildNo() - 1);
    findInorderPredecessor(key, predecessorKey, curNode, forceExtraction, success);
}

template <class type>
string BTree<type>::keyToString(type key){
    string keyString = "";
    ostringstream oss;
    oss.str("");
    oss.clear();
    oss << key;
    keyString += oss.str();
    return keyString;
}

template <class type>
bool BTree<type>::isValidBTreeString(string bTreeString){
    static CRegexpT<char> regexp(R"(\{\d+(,\d+)*\}(\(((?R),?)+\))*)");

    MatchResult result = regexp.MatchExact(bTreeString.c_str());

    return result.IsMatched();
}


template <class type>// TreeViz specific functions
void BTree<type>::toTreeString(BNode<type>* curNode, string &output){
    std::ostringstream oss;

    // Base Case
    if (curNode->isLeaf()){
        // wrap its contents with {}
        oss << "{";
        if (curNode->getColor() != "")
            oss << "*" << curNode->getColor() << "*";

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
    if (curNode->getColor() != "")
        oss << "*" << curNode->getColor() << "*";

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
    // cout << "at insert" << endl;
    // set leaf status
    if (parent)
        parent->setLeaf(false);
    if (child)
        child->setLeaf(true);

    if (parent == NULL){
        // cout << "a new root " << child << endl;
        root = child;
        return;
    }

    // cout << "adding a child " << child << " to parent " << parent << endl;
    // cout << "child no " << parent->getChildNo() << endl;
    parent->addChild(child, parent->getChildNo());
    // cout << "child pushed" << endl;
}

template <class type>
void BTree<type>::generateInorderSequence(BNode<type>* curNode, string &sequence){
    // Base case 1
    if (curNode == NULL)
        return;

    // Base case 2 - leaf - print keys only
    if (curNode->isLeaf()){
        for (int i = 0; i < curNode->getKeyNo(); i++){
            if(sequence.size() > 0)
                sequence += "," + keyToString(curNode->getKey(i));
            else
                sequence += keyToString(curNode->getKey(i));
        }
        return;
    }

    // add children
    for (int i = 0; i < curNode->getChildNo(); i++){
        generateInorderSequence(curNode->getChild(i), sequence);
        if (i < curNode->getKeyNo())
            sequence += "," + keyToString(curNode->getKey(i));
    }
}

template <class type>
void BTree<type>::recordStep(string stepText, string note){
    Step step;
    step.treeStr = toTreeString();
    step.text = stepText;
    step.note = note;
    
    this->steps.push_back(step);
}

template class BTree<int>;


int main(){

    BTree<int>* tree1 = new BTree<int>(3);
    // for (int i = 0; i < 1700 ; i++){
    //     tree1->insert(i);  
    // }

    // cout << "is valid " << tree1->constructFromTreeString("{5,8,12}({3}({1}{4}),{6}({5}{7}),{10}({9}{11}),{14}({13}{15}))") << endl;
    // cout << "is valid " << tree1->insertSequence("1,2,3,4,5,6,7,8,9,11,10") << endl;
    // tree1->constructFromTreeString("{8}({1})");
    
    // tree1->constructFromTreeString("{50}({1}{2,3}{3}{4})");
    // tree1->setSequence(tree1->generateInorderSequence());
    tree1->insertSequence("1");
    tree1->insert(2);

    tree1->insert(33);  
    tree1->insert(42); 
    tree1->insert(42); 
    tree1->insert(-3);  
    // tree1->insert(1);
    // // tree1->remove(1);
    // tree1->insert(2);  
    // tree1->remove(3);
    // tree1->remove(-3);

    cout << "sequence : " << tree1->getSequence() << endl;
    cout << "sequence : " << tree1->generateInorderSequence() << endl;

    // cout << "before" << endl;
    tree1->traverse();

    
    vector<Step> myVector = tree1->getSteps();
    cout << "size " << myVector.size() << endl;
    for (Step step : myVector){
        cout << "text : " << step.text << endl;
        cout << "tree : " << step.treeStr << endl;
    }

    return 0;
}