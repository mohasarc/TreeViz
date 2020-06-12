#include "../Header_Files/BSTree.h"

template <class T>
BSTree<T>::BSTree(){
    this->root = NULL;
    this->sequence = "";
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
bool BSTree<T>::remove(T anItem, char type){
    bool success = false;

    switch (type)
    {
    case 's':
    case 'S':
        TreeNode<T>* toBeDeleted;
        TreeNode<T>* toBeDeletedParent;
        toBeDeleted = this->root;
        search(toBeDeleted, toBeDeletedParent, anItem);

        if (toBeDeleted)
            this->removeWithSuccessor(toBeDeleted, toBeDeletedParent, success);

        if (success)
            this->sequence += ",d" + keyToString(anItem);

        return success;
    break;
    
    case 'p':
    case 'P':
        return false;
    break;

    default:
        return false;
        break;
    }
}

template <class T>
bool BSTree<T>::isEmpty(){
    return root == NULL;
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
                remove(stoi(numStr.substr(1)), 's');
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
    if (root == NULL)
        return;

    // Base case 2 - if found return
    if (anItem == root->getItem())
        return;

    parent = root;
    if (anItem < root->getItem()){
        root = root->getLeftChildPtr();
        search(root, parent, anItem);
    }
    else{
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
        TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
        tmpNode->setNewlyInserted(true);
        if (anItem < root->getItem()){
            root->setLeftChildPtr(tmpNode);
        } else {
            root->setRightChildPtr(tmpNode);
        }

        // Give feedback
        success = true;

        return;
    }

    // cout << "left child : " << (root->getLeftChildPtr() != NULL ? root->getLeftChildPtr()->getItem() : 0) 
    //      << "  rightChild   " << (root->getRightChildPtr() != NULL? root->getRightChildPtr()->getItem() : 0)  << endl; 

    // Either go left or make new node there
    if (anItem < root->getItem()){
        if (root->getLeftChildPtr() != NULL)
            insert(root->getLeftChildPtr(), anItem, success);
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setLeftChildPtr(tmpNode);

            // Give feedback
            success = true;
        }
    }
    // Either go right or make new node there
    else {
        if (root->getRightChildPtr() != NULL)
            insert(root->getRightChildPtr(), anItem, success);
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setRightChildPtr(tmpNode);

            // Give feedback
            success = true;
        }
    }
}

template <class T>
void BSTree<T>::removeWithSuccessor(TreeNode<T>* root, TreeNode<T>* parent, bool &success){
    // if leaf just remove it
    if (root->isLeaf()){
        if (parent->getLeftChildPtr() == root){
            // delete the child to the left
            parent->setLeftChildPtr(NULL);
        } else {
            // delete the child to the left
            parent->setRightChildPtr(NULL);
        }

        delete root;
        success = true;
        return;
    }

    // if has one child, make parent point to child's child
    if (root->getLeftChildPtr() == NULL || root->getRightChildPtr() == NULL){
        TreeNode<T>* tmp = root;
        if (parent->getLeftChildPtr() == root){
            // delete the child to the left
            parent->setLeftChildPtr((root->getLeftChildPtr() != NULL 
                                    ? root->getLeftChildPtr() 
                                    : root->getRightChildPtr()));
        } else {
            // delete the child to the right
            parent->setRightChildPtr((root->getLeftChildPtr() != NULL 
                                    ? root->getLeftChildPtr() 
                                    : root->getRightChildPtr()));
        }

        delete root;
        success = true;
        return;
    }

    // if root has both children, replace with inorder successor
    // and delete it from there leaf node
    TreeNode<T>* inSuccParent = NULL;
    TreeNode<T>* inorderSuccessor = root->getRightChildPtr()->getLeftChildPtr() == NULL 
                                    ? root->getRightChildPtr() 
                                    : getMostLeft(root->getRightChildPtr(), inSuccParent);
    if (inSuccParent == NULL) inSuccParent = root;

    // replace with inorder successor
    T tmpItem = root->getItem();
    root->setItem(inorderSuccessor->getItem());
    removeWithSuccessor(inorderSuccessor, inSuccParent, success);
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
        // oss << "{";
        oss << (root->getNewlyInserted() ? "{*" : "{");
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
    oss << (root->getNewlyInserted() ? "{*" : "{");
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

template class BSTree<int>;

int main(){
    BSTree<int> tree;

    // tree.insert(1);
    // tree.insert(2);
    // tree.insert(3);
    // tree.insert(4);
    // tree.insert(5);

    // tree.insertSequence("1,2,3,5,4,12,-5,33,6,7,8,9,d6,d-5");
    tree.constructFromTreeString("{35}({26}({24}({19}({},{*20}),{}),{29}({},{*34})),{89}({68}({53}({50}({46}({},{*49}),{}),{}),{}),{92}({},{*95})))");
    
    tree.setSequence(tree.generateInorderSequence());
    cout << endl;
    tree.remove(35,'s');
    tree.remove(7,'s');

    cout << tree.getSequence() << endl;
    cout << tree.generateInorderSequence() << endl;
    cout << tree.toTreeString() << endl;
    // cout << tree.traverse() << endl;
    return 0;
}