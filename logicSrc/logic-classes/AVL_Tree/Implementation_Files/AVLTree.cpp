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
    TreeNode<T>* updatedPtr = NULL;
    insert(root, anItem, updatedPtr);

    return true; // HARD CODED -- Might need to be changed
}

template <class T>
void AVLTree<T>::insert(TreeNode<T>* cur, T &anItem, TreeNode<T>* &updatePtr){
    cout << "inserting " << anItem << endl;
    // If empty insert at root
    if (isEmpty()){
        root = new TreeNode<T>(anItem);
        cout << "inserting at root " << root->getItem() << endl;
        return;
    }

    // Find the location to insert
    // Not Leaf
    // if (!cur->isLeaf()){
    //     cout << "not a leaf" << cur->getItem() << endl;
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
    // }
    // Leaf OR returning
    // else {
    //     // Leaf node
    //     cout << "insering at a leaf node " << endl;
    //     if (anItem < cur->getItem())
    //         cur->setLeftChildPtr(new TreeNode<T>(anItem));
    //     else 
    //         cur->setRightChildPtr(new TreeNode<T>(anItem));
    // }

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
        cout << aNode->getLeftChildPtr() << "  " << aNode->getLeftChildPtr()->getRightChildPtr() << endl;
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
    rotateL(leftChild, rightGrandChild);
    parent->setRightChildPtr(updatePtr);
    rotateR(parent, leftChild);
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
    if (parent == NULL){
        this->root = child;
        return;
    }

    if (parent->getLeftChildPtr() == NULL && !parent->doesLeftChildExist()){
        parent->setLeftChildPtr(child);
        parent->leftChildExistance(true);
    } else if (parent->getRightChildPtr() == NULL){
        parent->setRightChildPtr(child);
    }
}

template <class T>
string AVLTree<T>::keyToString(T key){
    string keyString = "";
    ostringstream oss;
    oss.str("");
    oss.clear();
    oss << key;
    keyString += oss.str();
    return keyString;
}

template <class T>
bool AVLTree<T>::isValidBSTreeString(string bsTreeString){
    static CRegexpT<char> regexp(R"(\{\*?\d*\}(\(((?R)(,(?R))?)?\))*)");

    MatchResult result = regexp.MatchExact(bsTreeString.c_str());

    return result.IsMatched();
}

template <class T>
void AVLTree<T>::generateInorderSequence(TreeNode<T>* curNode, string &sequence){
    // Base case - NULL, return
    if (curNode == NULL)
        return;

    // add left child
    generateInorderSequence(curNode->getLeftChildPtr(), sequence);

    // add self
    if(sequence.size() > 0)
        sequence += "," + keyToString(curNode->getItem());
    else
        sequence += keyToString(curNode->getItem());

    // add right child
    generateInorderSequence(curNode->getRightChildPtr(), sequence);
}

template <class T>
void AVLTree<T>::recordStep(string stepText, string note){
    Step step;
    step.treeStr = toTreeString();
    step.text = stepText;
    step.note = note;

    this->steps.push_back(step);
}

template <class T>
void AVLTree<T>::constructFromTreeString(const string treeString){
    stack<TreeNode<T>*> parentsStack;
    TreeNode<T>* tmpNode;
    bool treeNodeConstructed = false;

    // Validate the tree string
    if (!isValidBSTreeString(treeString)){
        // Not valid
        return;
    }
    
    for (int i = 0; i < treeString.length(); i++){
        switch (treeString.at(i))
        {
        case '{':
        tmpNode = new TreeNode<T>();
        treeNodeConstructed = tmpNode->construct(treeString.substr(i));
        if (root == NULL){
            insert(tmpNode, NULL);
        } else {
            // it it was constructed add it to tree, otherwise insert NULL
            if ( treeNodeConstructed ){
                insert(tmpNode, parentsStack.top());
            }
            else 
                insert(NULL, parentsStack.top());
        }

        // update stack
        parentsStack.push(tmpNode);
        break;

        case '}':
            // if node has no children pop it from parents
            if (treeString[i+1] != '('){
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
            parentsStack.pop();
            break;

        default:
            break;
        }
    }
}

template <class T>
string AVLTree<T>::toTreeString(){
    string outStr = "";
    this->toTreeString(root, outStr);
    return outStr;
}

template <class T>
bool AVLTree<T>::insertSequence(string sequence){
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

template <class T>
void AVLTree<T>::setSequence(string sequence){
    this->sequence = sequence;
}

template <class T>
string AVLTree<T>::getSequence(){
    return this->sequence;
}

template <class T>
string AVLTree<T>::generateInorderSequence(){
    string theSequence;
    this->generateInorderSequence(this->root, theSequence);
    return theSequence;
}

template <class T>
vector<Step> AVLTree<T>::getSteps(){
    return this->steps;
}

template <class T>
int AVLTree<T>::getStepsNo(){
    return this->steps.size();
}

template <class T>
string AVLTree<T>::getStepText(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].text;
    return "";
}

template <class T>
string AVLTree<T>::getStepTreeStr(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].treeStr;
    return "";
}

template <class T>
string AVLTree<T>::getStepNote(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].note;
    return "";
}

template <class T>
void AVLTree<T>::clearSteps(){
    this->steps.clear();
}

template class AVLTree<int>;
// template class AVLTree<string>;

int main (){
    AVLTree<int>* tree = new AVLTree<int>();
    // tree->insert(10);
    // cout << "1" << endl;
    // tree->insert(5);
    // cout << "2" << endl;
    // tree->insert(2);
    // cout << "3" << endl;
    // tree->insert(3);
    // cout << "4" << endl;
    // tree->insert(7);
    // cout << "5" << endl;
    // tree->insert(1);
    // cout << "6" << endl;

    // tree->constructFromTreeString("{5}({2}({1},{3}),{10}({7},{}))");
    tree->insertSequence("1,2,3,4,5,6,7,8,9");
    cout << tree->traverse();
    cout << "7" << endl;
    cout << tree->toTreeString();
    cout << "8" << endl;
    return 0;
}