#include "../Header_Files/BSTree.h"

template <class T>
BSTree<T>::BSTree(){
    this->root = NULL;
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
    return this->search(root, notUsed, anItem);
}

template <class T>
bool BSTree<T>::insert(T anItem){
    if (this->root == NULL){
        this->root = new TreeNode<T>(anItem);
        return true;
    }
    else {
        this->insert(this->root, anItem);
        return true;
    }
}

template <class T>
bool BSTree<T>::remove(T anItem, char type){
    switch (type)
    {
    case 's':
    case 'S':
        TreeNode<T>* toBeDeleted;
        TreeNode<T>* toBeDeletedParent;
        toBeDeleted = search(this->root, toBeDeletedParent, anItem);
        return this->removeWithSuccessor(toBeDeleted, toBeDeletedParent);
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
TreeNode<T>* BSTree<T>::search(TreeNode<T>* root, TreeNode<T>* &parent, T anItem){
    if (root == NULL)
        return NULL;

    if (anItem == root->getItem())
        return root;

    parent = root;
    if (anItem < root->getItem())
        search(root->getLeftChildPtr(), parent, anItem);
    else 
        search(root->getRightChildPtr(), parent, anItem);

    // For compiler to be happy
    return NULL;
}

template <class T>
void BSTree<T>::insert(TreeNode<T>* root, T &anItem){
    // Base case -- if leaf node insert at it
    if (root->isLeaf()){
        TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
        tmpNode->setNewlyInserted(true);
        if (anItem < root->getItem()){
            root->setLeftChildPtr(tmpNode);
        } else {
            root->setRightChildPtr(tmpNode);
        }

        return;
    }

    // cout << "left child : " << (root->getLeftChildPtr() != NULL ? root->getLeftChildPtr()->getItem() : 0) 
    //      << "  rightChild   " << (root->getRightChildPtr() != NULL? root->getRightChildPtr()->getItem() : 0)  << endl; 
    
    // Reset newlyInserted of all other nodes to false
    root->setNewlyInserted(false);

    // Either go left or make new node there
    if (anItem < root->getItem()){
        if (root->getLeftChildPtr() != NULL)
            insert(root->getLeftChildPtr(), anItem);
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setLeftChildPtr(tmpNode);
        }
    }
    // Either go right or make new node there
    else {
        if (root->getRightChildPtr() != NULL)
            insert(root->getRightChildPtr(), anItem);
        else{
            TreeNode<T> *tmpNode = new TreeNode<T>(anItem);
            tmpNode->setNewlyInserted(true);
            root->setRightChildPtr(tmpNode);
        }
    }
}

template <class T>
bool BSTree<T>::removeWithSuccessor(TreeNode<T>* root, TreeNode<T>* parent){
    // if leaf just remove it
    if (root->isLeaf()){
        delete root;
        if (parent->getLeftChildPtr() == root){
            // delete the child to the left
            parent->setLeftChildPtr(NULL);
        } else {
            // delete the child to the left
            parent->setRightChildPtr(NULL);
        }
        return true;
    }

    // if has one child, make parent point to child
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
        return true;
    }

    // if has both children, replace with inorder successor
    // and delete it from there leaf node
    TreeNode<T>* inSuccParent = NULL;
    TreeNode<T>* inorderSuccessor = root->getRightChildPtr()->getLeftChildPtr() == NULL 
                                    ? root->getRightChildPtr() 
                                    : getMostLeft(root->getRightChildPtr(), inSuccParent);
    if (inSuccParent == NULL) inSuccParent = root;

    // replace with inorder successor
    T tmpItem = root->getItem();
    root->setItem(inorderSuccessor->getItem());
    removeWithSuccessor(inorderSuccessor, inSuccParent);

    // for compiler to be happy
    return false;
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
        cout << "pushing father " << tmpNode->getItem() << endl;
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
bool BSTree<T>::isValidBSTreeString(string bsTreeString){
    static CRegexpT<char> regexp(R"(\{\*?\d*\}(\(((?R)(,(?R))?)?\))*)");

    MatchResult result = regexp.MatchExact(bsTreeString.c_str());

    return result.IsMatched();
}

template class BSTree<int>;