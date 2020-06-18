#include "../Header_Files/BSTree.h"

template <class T>
BSTree<T>::BSTree(){
    this->root = NULL;
    this->sequence = "";
    this->prioritizePredecessor = false;
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
        this->insert(this->root, anItem, success);
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
    TreeNode<T>* toBeDeleted = NULL;
    TreeNode<T>* toBeDeletedParent = NULL;

    // Find the node to be deleted
    toBeDeleted = this->root;
    search(toBeDeleted, toBeDeletedParent, anItem);

    // mark node to be deleted
    toBeDeleted->setColor("danger");
    recordStep("", "");

    // if the node is leaf just remove it
    if (toBeDeleted->isLeaf()){

        toBeDeleted->setEmpty(true);
        recordStep("", "");

        if (toBeDeletedParent){
            if (toBeDeletedParent->getLeftChildPtr() == toBeDeleted){
                // delete the child to the left
                toBeDeletedParent->setLeftChildPtr(NULL);
            } else {
                // delete the child to the left
                toBeDeletedParent->setRightChildPtr(NULL);
            }
        }

        recordStep("It is a leaf node: only delete it", "");

        delete toBeDeleted;
        if (!toBeDeletedParent)
            this->root = NULL;

        success = true;
        return success;
    }

    // If node to be deleted is the root and it has one child
    if (!toBeDeletedParent && (toBeDeleted->getLeftChildPtr() == NULL || toBeDeleted->getRightChildPtr() == NULL)){
        if (toBeDeleted->getLeftChildPtr() != NULL){
            // make it the root
            toBeDeleted->setEmpty(true);
            recordStep("", "");

            toBeDeleted->getLeftChildPtr()->setColor("alert");
            recordStep("The node is the root, make its left child the root", "");

            this->root = toBeDeleted->getLeftChildPtr();

            recordStep("", "");
            toBeDeleted->getLeftChildPtr()->setColor("");
        } else {
            // make right child the root
            toBeDeleted->setEmpty(true);
            recordStep("", "");

            toBeDeleted->getRightChildPtr()->setColor("alert");
            recordStep("The node is the root, make its left child the root", "");

            this->root = toBeDeleted->getRightChildPtr();

            recordStep("", "");
            toBeDeleted->getRightChildPtr()->setColor("");
        }

        delete toBeDeleted;
        success = true;
        return success;
    }

    // if has one child, make parent point to child's child
    if (toBeDeleted->getLeftChildPtr() == NULL || toBeDeleted->getRightChildPtr() == NULL){
        toBeDeleted->setEmpty(true);
        recordStep("", "");

        TreeNode<T>* tmp = toBeDeleted;
        if (toBeDeletedParent->getLeftChildPtr() == toBeDeleted){
            // delete the child to the left
            if (toBeDeleted->getLeftChildPtr() != NULL){

                toBeDeletedParent->setColor("alert");
                toBeDeleted->getLeftChildPtr()->setColor("alert");
                recordStep("The node has one left child: conect its toBeDeletedParent with its left child", "");

                toBeDeletedParent->setLeftChildPtr(toBeDeleted->getLeftChildPtr());

                toBeDeletedParent->setColor("success");
                toBeDeletedParent->getLeftChildPtr()->setColor("success");
                recordStep("The node was removed successfully", "");
                toBeDeletedParent->setColor("");
                toBeDeletedParent->getLeftChildPtr()->setColor("");
            } else {
                toBeDeletedParent->setColor("alert");
                toBeDeleted->getRightChildPtr()->setColor("alert");
                recordStep("The node has one right child: conect toBeDeletedParent and right child", "");

                toBeDeletedParent->setLeftChildPtr(toBeDeleted->getRightChildPtr());

                toBeDeletedParent->setColor("success");
                toBeDeletedParent->getLeftChildPtr()->setColor("success");
                recordStep("The node was removed successfully", "");
                toBeDeletedParent->setColor("");
                toBeDeletedParent->getLeftChildPtr()->setColor("");
            }
            // toBeDeletedParent->setLeftChildPtr((toBeDeleted->getLeftChildPtr() != NULL 
            //                         ? toBeDeleted->getLeftChildPtr() 
            //                         : toBeDeleted->getRightChildPtr()));
        } else {
            // delete the child to the right
            if (toBeDeleted->getLeftChildPtr() != NULL ){

                toBeDeletedParent->setColor("alert");
                toBeDeleted->getLeftChildPtr()->setColor("alert");
                recordStep("The node has one left child: conect its toBeDeletedParent with its left child", "");

                toBeDeletedParent->setRightChildPtr(toBeDeleted->getLeftChildPtr());

                toBeDeletedParent->setColor("success");
                toBeDeletedParent->getRightChildPtr()->setColor("success");
                recordStep("The node was removed successfully", "");
                toBeDeletedParent->setColor("");
                toBeDeletedParent->getRightChildPtr()->setColor("");
            } else {
                toBeDeletedParent->setColor("alert");
                toBeDeleted->getRightChildPtr()->setColor("alert");
                recordStep("The node has one right child: conect toBeDeletedParent and right child", "");

                toBeDeletedParent->setRightChildPtr(toBeDeleted->getRightChildPtr());

                toBeDeletedParent->setColor("success");
                toBeDeletedParent->getRightChildPtr()->setColor("success");
                recordStep("The node was removed successfully", "");
                toBeDeletedParent->setColor("");
                toBeDeletedParent->getRightChildPtr()->setColor("");
            }

            // parent->setRightChildPtr((toBeDeleted->getLeftChildPtr() != NULL 
            //                         ? toBeDeleted->getLeftChildPtr() 
            //                         : toBeDeleted->getRightChildPtr()));
        }

        delete toBeDeleted;
        success = true;
        return success;
    }

    if (this->prioritizePredecessor){
        if (toBeDeleted){
            this->removeWithPredecessor(toBeDeleted, toBeDeletedParent, success);
        }

        if (success)
            this->sequence += ",d" + keyToString(anItem);

        return success;
    } else {
        if (toBeDeleted){
            this->removeWithSuccessor(toBeDeleted, toBeDeletedParent, success);
        }

        if (success)
            this->sequence += ",d" + keyToString(anItem);

        return success;
    }
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
void BSTree<T>::insert(TreeNode<T>* root, T &anItem, bool &success){
    // Reset newlyInserted of all other nodes to false
    root->setNewlyInserted(false);

    // Base case -- if leaf node insert at it
    if (root->isLeaf()){
        // set the node to be selected, record step, then unselect it
        root->setColor("select");
        recordStep("Reached a leaf node, insert at it", "");
        root->setColor("");

        TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
        tmpNode->setNewlyInserted(true);
        tmpNode->setColor("success");
        if (anItem < root->getItem()){
            root->setLeftChildPtr(tmpNode);
            recordStep("Item is less than item in the leaf, so insert at left", "");
        } else {
            root->setRightChildPtr(tmpNode);
            recordStep("Item is greater than item in the leaf, so insert at right", "");
        }
        tmpNode->setColor("");

        // Give feedback
        success = true;

        return;
    }

    // cout << "left child : " << (root->getLeftChildPtr() != NULL ? root->getLeftChildPtr()->getItem() : 0) 
    //      << "  rightChild   " << (root->getRightChildPtr() != NULL? root->getRightChildPtr()->getItem() : 0)  << endl; 

    // Either go left or make new node there
    if (anItem < root->getItem()){
        // Record a step
        root->setColor("select");
        recordStep("Key to be inserted < key being checked, check left", "");
        root->setColor("");

        if (root->getLeftChildPtr() != NULL){
            insert(root->getLeftChildPtr(), anItem, success);
        }
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setLeftChildPtr(tmpNode);
            
            // Record a step
            tmpNode->setColor("success");
            recordStep("The is no left child, insert here", "");
            tmpNode->setColor("");

            // Give feedback
            success = true;
        }
    }
    // Either go right or make new node there
    else {
        // Record a step
        root->setColor("select");
        recordStep("Key to be inserted >= key being checked, check right", "");
        root->setColor("");

        if (root->getRightChildPtr() != NULL)
            insert(root->getRightChildPtr(), anItem, success);
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setRightChildPtr(tmpNode);

            // Record a step
            tmpNode->setColor("success");
            recordStep("The is no right child, insert here", "");
            tmpNode->setColor("");

            // Give feedback
            success = true;
        }
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

template <class type>
void BSTree<type>::clearSteps(){
    this->steps.clear();
}

template class BSTree<int>;

int main(){
    BSTree<int> tree;

    // tree.insert(1);
    // tree.insert(2);
    // tree.insert(3);
    // tree.insert(4);
    // tree.insert(5);

    tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9,d6,d-5");
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