#include "../Header_Files/BSTree.h"

template <class T>
BSTree<T>::BSTree(bool balanced){
    this->root = NULL;
    this->sequence = "";
    this->prioritizePredecessor = false;
    this->balanced = balanced;

    cout << this->balanced << endl;
}

template <class T>
string BSTree<T>::traverse(){
    string outStr = "";
    this->traverse(this->root, outStr);
    return outStr;
}

template <class T>
bool BSTree<T>::search(T anItem){
    TreeNode<T>* notUsed;
    this->search(root, notUsed, anItem);

    return root;
}

template <class T>
bool BSTree<T>::insert(T anItem){
    bool success = false;
    if (this->root == NULL){
        this->root = new TreeNode<T>(anItem);
        this->root->setColor("success");
        recordStep("Root is null, insert at it", "");
        this->root->setColor("");

        success = true;
    }
    else {
        this->insert(this->root, NULL, anItem, success);
    }

    if (success){
        // add key to the sequence
        if (this->sequence.size() > 0)
            sequence += "," + keyToString(anItem);
        else
            sequence += keyToString(anItem);
    }

    return success;
}

template <class T>
bool BSTree<T>::remove(T anItem){
    bool success = false;

    if (this->root){
        remove(this->root, NULL, anItem, success);
    }

    if (success)
    this->sequence += ",d" + keyToString(anItem);
}

template <class T>
bool BSTree<T>::isEmpty(){
    return root == NULL;
}

template <class T>
void BSTree<T>::setPrioritizePredecessor(bool prioritizePredecessor){
    this->prioritizePredecessor = prioritizePredecessor;
}

template <class T>
string BSTree<T>::toTreeString(){
    string treeStr = "";

    if (this->root)
        this->toTreeString(this->root, treeStr);
    return treeStr;
}

template <class T>
bool BSTree<T>::insertSequence(string sequence){
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
void BSTree<T>::setSequence(string sequence){
    this->sequence = sequence;
}

template <class T>
string BSTree<T>::getSequence(){
    return this->sequence;
}

template <class T>
string BSTree<T>::generateInorderSequence(){
    string theSequence;
    this->generateInorderSequence(this->root, theSequence);
    return theSequence;
}

template <class T>
vector<Step> BSTree<T>::getSteps(){
    return this->steps;
}

template <class T>
int BSTree<T>::getStepsNo(){
    return this->steps.size();
}

template <class T>
string BSTree<T>::getStepText(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].text;
    return "";
}

template <class T>
string BSTree<T>::getStepTreeStr(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].treeStr;
    return "";
}

template <class T>
string BSTree<T>::getStepNote(int index){
    if (index >= 0 && index < this->steps.size());
        return this->steps[index].note;
    return "";
}

// Private Methods
template <class T>
void BSTree<T>::traverse(TreeNode<T>* root, string &outStr){
    // Stopping case -- reached leaf node or NULL node
    if (root == NULL)
        return;
    // print left subtree
    traverse(root->getLeftChildPtr(), outStr);

    // print selt
    ostringstream oss;
    oss << root->getItem();
    outStr += oss.str() + "\t";
    oss.str("");
    oss.clear();

    // print right subtree
    traverse(root->getRightChildPtr(), outStr);


}

template <class T>
void BSTree<T>::search(TreeNode<T>* &root, TreeNode<T>* &parent, T anItem){
    // Base case 1 - not found return
    if (root == NULL){
        recordStep("Key could not be found!", "");
        return;
    }

    // Base case 2 - if found return
    if (anItem == root->getItem()){
        root->setColor("select");
        recordStep("Key was found", "");
        root->setColor("");
        return;
    }

    parent = root;
    if (anItem < root->getItem()){
        root->setColor("select");
        recordStep("Target key < current key: goo t left child", "");
        root->setColor("");

        root = root->getLeftChildPtr();
        search(root, parent, anItem);
    }
    else{
        root->setColor("select");
        recordStep("Target key > current key: goo t right child", "");
        root->setColor("");

        root = root->getRightChildPtr();
        search(root, parent, anItem);
    }
}

template <class T>
void BSTree<T>::insert(TreeNode<T>* curNode, TreeNode<T>* parent, T &anItem, bool &success){
    cout << "inserting " << anItem << endl;
    // Reset newlyInserted of all other nodes to false
    curNode->setNewlyInserted(false);

    // Base case -- if leaf node insert at it
    if (curNode->isLeaf()){
        // set the node to be selected, record step, then unselect it
        curNode->setColor("select");
        recordStep("Reached a leaf node, insert at it", "");
        curNode->setColor("");

        TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
        tmpNode->setNewlyInserted(true);
        tmpNode->setColor("success");
        if (anItem < curNode->getItem()){
            curNode->setLeftChildPtr(tmpNode);
            recordStep("Item is less than item in the leaf, so insert at left", "");
        } else {
            curNode->setRightChildPtr(tmpNode);
            recordStep("Item is greater than item in the leaf, so insert at right", "");
        }
        tmpNode->setColor("");

        // Update the height of current node
        if (curNode->getHeight() <= tmpNode->getHeight()){
            cout << "updating height" << endl;
            curNode->setHeight(tmpNode->getHeight() + 1);
        }

        // Give feedback
        success = true;

        return;
    }

    // cout << "left child : " << (curNode->getLeftChildPtr() != NULL ? curNode->getLeftChildPtr()->getItem() : 0) 
    //      << "  rightChild   " << (curNode->getRightChildPtr() != NULL? curNode->getRightChildPtr()->getItem() : 0)  << endl; 

    // Either go left or make new node there
    if (anItem < curNode->getItem()){
        // Record a step
        curNode->setColor("select");
        recordStep("Key to be inserted < key being checked, check left", "");
        curNode->setColor("");

        if (curNode->getLeftChildPtr() != NULL){
            insert(curNode->getLeftChildPtr(), curNode, anItem, success);

            // Update the height of current node
            if (curNode->getHeight() <= curNode->getLeftChildPtr()->getHeight()){
                cout << "updating height" << endl;
                curNode->setHeight(curNode->getLeftChildPtr()->getHeight() + 1);
            }
        }
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            curNode->setLeftChildPtr(tmpNode);
            
            // Record a step
            tmpNode->setColor("success");
            recordStep("The is no left child, insert here", "");
            tmpNode->setColor("");

            // Update the height of current node
            if (curNode->getHeight() <= tmpNode->getHeight()){
                cout << "updating height" << endl;
                curNode->setHeight(tmpNode->getHeight() + 1);
            }

            // Give feedback
            success = true;
        }
    }
    // Either go right or make new node there
    else {
        // Record a step
        curNode->setColor("select");
        recordStep("Key to be inserted >= key being checked, check right", "");
        curNode->setColor("");

        if (curNode->getRightChildPtr() != NULL){
            insert(curNode->getRightChildPtr(), curNode, anItem, success);

            // Update the height of current node
            cout << "curnode " << curNode << " right child  " << curNode->getRightChildPtr() << endl;
            if (curNode->getHeight() <= curNode->getRightChildPtr()->getHeight()){
                cout << "updating height" << endl;
                curNode->setHeight(curNode->getRightChildPtr()->getHeight() + 1);
            }
        }
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            curNode->setRightChildPtr(tmpNode);

            // Record a step
            tmpNode->setColor("success");
            recordStep("The is no right child, insert here", "");
            tmpNode->setColor("");

            // Update the height of current node
            if (curNode->getHeight() <= tmpNode->getHeight()){
                cout << "updating height" << endl;
                curNode->setHeight(tmpNode->getHeight() + 1);
            }

            // Give feedback
            success = true;
        }
    }

    if (this->balanced){
        // Check balance
        cout << "balancing" << endl;
        balance(curNode, parent);
    }
}

template <class T>
void BSTree<T>::remove(TreeNode<T>* curNode, TreeNode<T>* parent, T anItem, bool &success){
    // Base case 1 - not found return
    if (curNode == NULL){
        recordStep("Key could not be found!", "");
        return;
    }

    // Base case 2 - if found return
    if (anItem == curNode->getItem()){
        curNode->setColor("select");
        recordStep("Key was found", "");
        curNode->setColor("");

        // mark node to be deleted
        curNode->setColor("danger");
        recordStep("", "");

        // if the node is leaf just remove it
        if (curNode->isLeaf()){

            curNode->setEmpty(true);
            recordStep("", "");

            if (parent){
                if (parent->getLeftChildPtr() == curNode){
                    // delete the child to the left
                    parent->setLeftChildPtr(NULL);
                } else {
                    // delete the child to the left
                    parent->setRightChildPtr(NULL);
                }
            }

            recordStep("It is a leaf node: only delete it", "");

            delete curNode;
            if (!parent)
                this->root = NULL;

            success = true;
            return;
        }

        // If node to be deleted is the root and it has one child
        if (!parent && (curNode->getLeftChildPtr() == NULL || curNode->getRightChildPtr() == NULL)){
            if (curNode->getLeftChildPtr() != NULL){
                // make it the root
                curNode->setEmpty(true);
                recordStep("", "");

                curNode->getLeftChildPtr()->setColor("alert");
                recordStep("The node is the root, make its left child the root", "");

                this->root = curNode->getLeftChildPtr();

                recordStep("", "");
                curNode->getLeftChildPtr()->setColor("");
            } else {
                // make right child the root
                curNode->setEmpty(true);
                recordStep("", "");

                curNode->getRightChildPtr()->setColor("alert");
                recordStep("The node is the root, make its left child the root", "");

                this->root = curNode->getRightChildPtr();

                recordStep("", "");
                curNode->getRightChildPtr()->setColor("");
            }

            delete curNode;
            success = true;
            return;
        }

        // if has one child, make parent point to child's child
        if (curNode->getLeftChildPtr() == NULL || curNode->getRightChildPtr() == NULL){
            curNode->setEmpty(true);
            recordStep("", "");

            TreeNode<T>* tmp = curNode;
            if (parent->getLeftChildPtr() == curNode){
                // delete the child to the left
                if (curNode->getLeftChildPtr() != NULL){

                    parent->setColor("alert");
                    curNode->getLeftChildPtr()->setColor("alert");
                    recordStep("The node has one left child: conect its parent with its left child", "");

                    parent->setLeftChildPtr(curNode->getLeftChildPtr());

                    parent->setColor("success");
                    parent->getLeftChildPtr()->setColor("success");
                    recordStep("The node was removed successfully", "");
                    parent->setColor("");
                    parent->getLeftChildPtr()->setColor("");
                } else {
                    parent->setColor("alert");
                    curNode->getRightChildPtr()->setColor("alert");
                    recordStep("The node has one right child: conect parent and right child", "");

                    parent->setLeftChildPtr(curNode->getRightChildPtr());

                    parent->setColor("success");
                    parent->getLeftChildPtr()->setColor("success");
                    recordStep("The node was removed successfully", "");
                    parent->setColor("");
                    parent->getLeftChildPtr()->setColor("");
                }
                // parent->setLeftChildPtr((toBeDeleted->getLeftChildPtr() != NULL 
                //                         ? toBeDeleted->getLeftChildPtr() 
                //                         : toBeDeleted->getRightChildPtr()));
            } else {
                // delete the child to the right
                if (curNode->getLeftChildPtr() != NULL ){

                    parent->setColor("alert");
                    curNode->getLeftChildPtr()->setColor("alert");
                    recordStep("The node has one left child: conect its parent with its left child", "");

                    parent->setRightChildPtr(curNode->getLeftChildPtr());

                    parent->setColor("success");
                    parent->getRightChildPtr()->setColor("success");
                    recordStep("The node was removed successfully", "");
                    parent->setColor("");
                    parent->getRightChildPtr()->setColor("");
                } else {
                    parent->setColor("alert");
                    curNode->getRightChildPtr()->setColor("alert");
                    recordStep("The node has one right child: conect parent and right child", "");

                    parent->setRightChildPtr(curNode->getRightChildPtr());

                    parent->setColor("success");
                    parent->getRightChildPtr()->setColor("success");
                    recordStep("The node was removed successfully", "");
                    parent->setColor("");
                    parent->getRightChildPtr()->setColor("");
                }

                // parent->setRightChildPtr((toBeDeleted->getLeftChildPtr() != NULL 
                //                         ? toBeDeleted->getLeftChildPtr() 
                //                         : toBeDeleted->getRightChildPtr()));
            }

            delete curNode;
            success = true;
            return;
        }

        if (this->prioritizePredecessor){
            if (curNode){
                this->removeWithPredecessor(curNode, parent, success);
            }

            return;
        } else {
            if (curNode){
                this->removeWithSuccessor(curNode, parent, success);
            }

            return;
        }

        return;
    }

    // parent = curNode;
    if (anItem < curNode->getItem()){
        curNode->setColor("select");
        recordStep("Target key < current key: go to left child", "");
        curNode->setColor("");

        remove(curNode->getLeftChildPtr(), curNode, anItem, success);
        cout << "returned from remove " << endl;
    }
    else{
        curNode->setColor("select");
        recordStep("Target key > current key: go to right child", "");
        curNode->setColor("");

        remove(curNode->getRightChildPtr(), curNode, anItem, success);
    }

    // Update height
    cout << "updating curNode height " << endl;
    int lChildHeight = 0, rChildHeight = 0;
    if(curNode->getLeftChildPtr()){
        lChildHeight = curNode->getLeftChildPtr()->getHeight();
    }
    if (curNode->getRightChildPtr()){
        rChildHeight = curNode->getRightChildPtr()->getHeight();
    }

    cout << "old height " << curNode->getHeight() << endl;
    curNode->setHeight(findMax(lChildHeight, rChildHeight) + 1);
    cout << "new height " << curNode->getHeight() << endl;

    if (this->balanced){
        balance(curNode, parent);
    }    
}

template <class T>
void BSTree<T>::removeWithSuccessor(TreeNode<T>* root, TreeNode<T>* parent, bool &success){
    // if root has both children, replace with inorder successor
    // and delete it from there leaf node
    TreeNode<T>* inSuccParent = NULL;
    TreeNode<T>* inorderSuccessor = root->getRightChildPtr()->getLeftChildPtr() == NULL 
                                    ? root->getRightChildPtr() 
                                    : getMostLeft(root->getRightChildPtr(), inSuccParent);
    if (inSuccParent == NULL) inSuccParent = root;

    inorderSuccessor->setColor("alert");
    recordStep("The node has two children, find its inorder successor", "");

    // replace with inorder successor
    T tmpItem = root->getItem();
    root->setItem(inorderSuccessor->getItem());
    recordStep("Replace the node with its inorder successor", "");

    root->setColor("");
    inorderSuccessor->setColor("danger");
    recordStep("Mark the inorder successor to be deleted", "");
    // root->setColor("");
    // inorderSuccessor->setColor("");

    if (inSuccParent){
        if (inSuccParent->getLeftChildPtr() == inorderSuccessor){
            inSuccParent->setLeftChildPtr(inorderSuccessor->getRightChildPtr());
        } else {
            inSuccParent->setRightChildPtr(inorderSuccessor->getRightChildPtr());
        }

        delete inorderSuccessor;
        success = true;
    }

    // Remove the inorder successor
    // success = remove(inorderSuccessor->getItem());
    // removeWithSuccessor(inorderSuccessor, inSuccParent, success);
}

template <class T>
void BSTree<T>::removeWithPredecessor(TreeNode<T>* root, TreeNode<T>* parent, bool &success){
    // if root has both children, replace with inorder predecessor
    // and delete it from there leaf node
    TreeNode<T>* inPredecParent = NULL;
    TreeNode<T>* inorderPredecessor = root->getLeftChildPtr()->getRightChildPtr() == NULL 
                                    ? root->getLeftChildPtr() 
                                    : getMostRight(root->getLeftChildPtr(), inPredecParent);
    if (inPredecParent == NULL) inPredecParent = root;

    inorderPredecessor->setColor("alert");
    recordStep("The node has two children, find its inorder predecessor", "");

    // replace with inorder predecessor
    T tmpItem = root->getItem();
    root->setItem(inorderPredecessor->getItem());
    recordStep("Replace the node with its inorder predecessor", "");

    root->setColor("");
    inorderPredecessor->setColor("danger");
    recordStep("Mark the inorder predecessor to be deleted", "");
    // root->setColor("");
    // inorderPredecessor->setColor("");

    if (inPredecParent){
        if (inPredecParent->getLeftChildPtr() == inorderPredecessor){
            inPredecParent->setLeftChildPtr(inorderPredecessor->getLeftChildPtr());
        } else {
            inPredecParent->setRightChildPtr(inorderPredecessor->getLeftChildPtr());
        }

        delete inorderPredecessor;
        success = true;
    }
}

template <class T>
void BSTree<T>::toTreeString(TreeNode<T>* root, string &output){
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
        if (root->getColor() != "")
            oss << "*" << root->getColor() << "*";
        // oss << (root->getNewlyInserted() ? "{*" : "{");
        oss << root->getItem();
        oss << "}";
        output += oss.str();
        oss.str("");
        oss.clear();
        return;
    }

    // Not a leaf
    // *** add self ***
    // oss << "{";
    // oss << (root->getNewlyInserted() ? "{*" : "{");
    oss << "{";
    if (root->getColor() != "")
        oss << "*" << root->getColor() << "*";
    if (!root->isEmpty())
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
void BSTree<T>::insert(TreeNode<T> *child, TreeNode<T> *parent){
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
void BSTree<T>::constructFromTreeString(const string treeString){
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
TreeNode<T>* BSTree<T>::getMostLeft(TreeNode<T>* root, TreeNode<T>* &parent){
    // Base case -- if left is null
    if (root->getLeftChildPtr() == NULL){
        return root;
    }

    parent = root;
    return getMostLeft(root->getLeftChildPtr(), parent);
}

template <class T>
TreeNode<T>* BSTree<T>::getMostRight(TreeNode<T>* root, TreeNode<T>* &parent){
    // Base case -- if left is null
    if (root->getRightChildPtr() == NULL){
        return root;
    }

    parent = root;
    return getMostRight(root->getRightChildPtr(), parent);
}

template <class T>
string BSTree<T>::keyToString(T key){
    string keyString = "";
    ostringstream oss;
    oss.str("");
    oss.clear();
    oss << key;
    keyString += oss.str();
    return keyString;
}

template <class T>
bool BSTree<T>::isValidBSTreeString(string bsTreeString){
    static CRegexpT<char> regexp(R"(\{\*?\d*\}(\(((?R)(,(?R))?)?\))*)");

    MatchResult result = regexp.MatchExact(bsTreeString.c_str());

    return result.IsMatched();
}

template <class T>
void BSTree<T>::generateInorderSequence(TreeNode<T>* curNode, string &sequence){
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
void BSTree<T>::recordStep(string stepText, string note){
    Step step;
    step.treeStr = toTreeString();
    step.text = stepText;
    step.note = note;

    this->steps.push_back(step);
}

template <class T>
void BSTree<T>::balance(TreeNode<T>* curNode, TreeNode<T>* parent){
    cout << "in balancing cur node" << curNode << " parent " << parent << endl;
    int lChildHeight = 0, rChildHeight = 0, lGrandChildHeight = 0, rGrandChildHeight = 0;
    int balanceFactor = 0;

    TreeNode<T> *rChild = curNode->getRightChildPtr(), *lChild = curNode->getLeftChildPtr(), 
                *rGrandChild, *lGrandChild;

    // Get the heights of the left and right children
    if (lChild){
        lChildHeight = lChild->getHeight();
    }

    if (rChild){
        rChildHeight = rChild->getHeight();
    }

    cout << "Got the heights of the left and right children" << endl;

    // Get the heights of left and right grand children
    if (lChildHeight > rChildHeight){
        if (lChild->getLeftChildPtr()){
            lGrandChild = lChild->getLeftChildPtr();
            lGrandChildHeight = lGrandChild->getHeight();
        }

        if (lChild->getRightChildPtr()){
            rGrandChild = lChild->getRightChildPtr();
            rGrandChildHeight = rGrandChild->getHeight();
        }
    } else if (lChildHeight < rChildHeight) {
        if (rChild->getLeftChildPtr()){
            lGrandChild = rChild->getLeftChildPtr();
            lGrandChildHeight = lGrandChild->getHeight();
        }

        if (rChild->getRightChildPtr()){
            rGrandChild = rChild->getRightChildPtr();
            rGrandChildHeight = rGrandChild->getHeight();
        }
    }

    cout << "Got the heights of left and right grand children" << endl;

    //calculate the balance factor
    balanceFactor = lChildHeight - rChildHeight;

    if (balanceFactor <= 1 && balanceFactor >= -1){
        // subtree is balanced 
        cout << "balanced" << endl;
        return;
    }

    // Not balanced

    // Rotate R
    if (lChildHeight > rChildHeight && lGrandChildHeight > rGrandChildHeight){
        rotateR(curNode, parent, lChild);
    }
    // Rotate L
    if (rChildHeight > lChildHeight && rGrandChildHeight > lGrandChildHeight){
        rotateL(curNode, parent, rChild);
    }
    // Rotate RL
    if (rChildHeight > lChildHeight && lGrandChildHeight > rGrandChildHeight){
        // Right rotate
        rotateR(rChild, curNode, lGrandChild);

        // Left rotate
        rotateL(curNode, parent, lGrandChild);
    }
    // Rotate LR
    if (lChildHeight > rChildHeight && rGrandChildHeight > lGrandChildHeight){
        // Left rotate
        rotateL(lChild, curNode, rGrandChild);
        
        // Right rotate
        rotateR(curNode, parent, rGrandChild);
    }
}

template <class T>
void BSTree<T>::rotateR(TreeNode<T>* curNode, TreeNode<T>* parent, TreeNode<T>* lChild){
    if (parent){
        cout << "performing right rotate " << parent->getItem() << " " << curNode->getItem() << " " << lChild->getItem() << endl;

        if (parent->getLeftChildPtr() == curNode){
            parent->setLeftChildPtr(lChild);
        } else {
            parent->setRightChildPtr(lChild);
        }
    } else {
        cout << "performing right rotate " << parent << " " << curNode->getItem() << " " << lChild->getItem() << endl;

        this->root = lChild;
    }

    // Move the right child of the node moved up to the cur node
    curNode->setLeftChildPtr(lChild->getRightChildPtr());
    // Make the cur node replace the right child of the node moved up
    lChild->setRightChildPtr(curNode);

    // Update the heights
    int lChildHeight = 0, rChildHeight = 0, biggerHeight = 0;
    if (curNode->getLeftChildPtr()){
        lChildHeight = curNode->getLeftChildPtr()->getHeight();
    }

    if (curNode->getRightChildPtr()){
        rChildHeight = curNode->getRightChildPtr()->getHeight();
    }

    lChildHeight > rChildHeight ? biggerHeight = lChildHeight : biggerHeight = rChildHeight;
    curNode->setHeight(biggerHeight + 1);

    if (lChild->getLeftChildPtr()){
        lChildHeight = lChild->getLeftChildPtr()->getHeight();
    }

    if (lChild->getRightChildPtr()){
        rChildHeight = lChild->getRightChildPtr()->getHeight();
    }

    lChildHeight > rChildHeight ? biggerHeight = lChildHeight : biggerHeight = rChildHeight;
    lChild->setHeight(biggerHeight + 1);
}

template <class T>
void BSTree<T>::rotateL(TreeNode<T>* curNode, TreeNode<T>* parent, TreeNode<T>* rChild){
    if (parent){
        cout << "performing left rotate " << parent->getItem() << " " << curNode->getItem() << " " << rChild->getItem() << endl;

        if (parent->getLeftChildPtr() == curNode){
            cout << "setting the left" << endl;
            parent->setLeftChildPtr(rChild);
        } else {
            cout << "setting the right" << endl;
            parent->setRightChildPtr(rChild);
        }
    } else {
        cout << "performing left rotate " << parent << " " << curNode->getItem() << " " << rChild->getItem() << endl;

        this->root = rChild;
    }

    curNode->setRightChildPtr(rChild->getLeftChildPtr());
    rChild->setLeftChildPtr(curNode);

    // Update the heights
    int lChildHeight = 0, rChildHeight = 0, biggerHeight = 0;
    if (curNode->getLeftChildPtr()){
        lChildHeight = curNode->getLeftChildPtr()->getHeight();
    }

    if (curNode->getRightChildPtr()){
        rChildHeight = curNode->getRightChildPtr()->getHeight();
    }

    lChildHeight > rChildHeight ? biggerHeight = lChildHeight : biggerHeight = rChildHeight;
    curNode->setHeight(biggerHeight + 1);

    if (rChild->getLeftChildPtr()){
        lChildHeight = rChild->getLeftChildPtr()->getHeight();
    }

    if (rChild->getRightChildPtr()){
        rChildHeight = rChild->getRightChildPtr()->getHeight();
    }

    lChildHeight > rChildHeight ? biggerHeight = lChildHeight : biggerHeight = rChildHeight;
    rChild->setHeight(biggerHeight + 1);

}


template <class T>
void BSTree<T>::clearSteps(){
    this->steps.clear();
}

template class BSTree<int>;

int main(){
    BSTree<int> tree(1);

    // tree.insert(1);
    // tree.insert(2);
    // tree.insert(3);
    // tree.insert(4);
    // tree.insert(5);

    // tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9");
    tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9,d1");
    // tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9,d1,d-5");
    // tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9,-10,20,13");
    // tree.constructFromTreeString("{35}({26}({24}({19}({},{*20}),{}),{29}({},{*34})),{89}({68}({53}({50}({46}({},{*49}),{}),{}),{}),{92}({},{*95})))");
    
    // tree.setSequence(tree.generateInorderSequence());
    cout << endl;
    // tree.remove(35,'s');
    // tree.insert(7);
    // tree.insert(6);
    // tree.remove(7,'s');

    cout << tree.getSequence() << endl;
    cout << tree.generateInorderSequence() << endl;
    cout << tree.toTreeString() << endl;

    vector<Step> myVector = tree.getSteps();
    cout << "size " << myVector.size() << endl;
    for (Step step : myVector){
        cout << "text : " << step.text << endl;
        cout << "tree : " << step.treeStr << endl;
    }

    // cout << tree.traverse() << endl;
    return 0;
}