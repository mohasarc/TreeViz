#include "../Header_Files/Tree23.h"
#include <sstream>

template <class T>
Tree23<T>::Tree23(){
    root = NULL;
}

template <class T>
string Tree23<T>::traverse(){
    string output;
    traverse(root, output);
    return output;
}

template <class T>
void Tree23<T>::traverse(TriNode<T>* root, string &output){
    // Base Case
    if (root->isLeaf()){
        // Print its contents
        output += root->getSmallItem() + "\t";
        cout << root->getSmallItem() << "\t";
        if (root->isThreeNode()){
            output += root->getLargeItem() + "\t";
            cout << root->getLargeItem() << "\t";
        }
        return;
    }

    // Not a leaf
    // Print Left
    traverse(root->getLeftChildPtr(), output);

    // Print Smaller Item
    output += root->getSmallItem() + "\t";
    cout << root->getSmallItem() << "\t";

    // Print Middle
    traverse(root->getMidChildPtr(), output);

    if (root->isThreeNode()) {
        // Print Larger Item
        output += root->getLargeItem() + "\t";
        cout << root->getLargeItem() << "\t";

        // Print Right
        traverse(root->getRightChildPtr(), output);
    }
}

template <class T>
bool Tree23<T>::search(T anItem){
    return search(root, anItem, NULL);
}

template <class T>
bool Tree23<T>::search(TriNode<T>* root, T anItem, TriNode<T>* foundLocation){
    // update foundlocation
    foundLocation = root;

    // If the item at the root
    if (root->getSmallItem() == anItem)
        return true;
    if (root->isThreeNode() && root->getLargeItem() == anItem)
        return true;

    // Base Case
    if (root->isLeaf()){
        return false;
    }

    // Item is not in the root
    if (anItem < root->getSmallItem())
        search(root->getLeftChildPtr(), anItem, NULL);
    else {
        // Either middle or right
        if (root->isTwoNode())
            search(root->getMidChildPtr(), anItem, NULL);
        else {
            if (anItem < root->getLargeItem())
                search(root->getMidChildPtr(), anItem, NULL);
            else 
                search(root->getRightChildPtr(), anItem, NULL);
        }
    }

    return false;
}

template <class T>
bool Tree23<T>::insert(T anItem){
    // cout << "calling insert" << endl;
    TriNode<T>* newPtr = NULL;
    insert(root, anItem, newPtr);
    return true;
}

template <class T>
void Tree23<T>::insert(TriNode<T>* cur, T &anItem, TriNode<T>* &newPtr){

    // The tree is empty    
    if (root == NULL){
        // cout << "adding to root" << "\t";
        root = new TriNode<T>(anItem);
        // cout << root->getSmallItem() << endl;
        return;
    }
    
    // Item is not in the root
    if (!cur->isLeaf()){
        // cout << "adding to an inner node" << endl;
        if (anItem < cur->getSmallItem())
            insert(cur->getLeftChildPtr(), anItem, newPtr);
        else {
            // Either middle or right
            if (cur->isTwoNode())
                insert(cur->getMidChildPtr(), anItem, newPtr);
            else {
                if (anItem < cur->getLargeItem())
                    insert(cur->getMidChildPtr(), anItem, newPtr);
                else 
                    insert(cur->getRightChildPtr(), anItem, newPtr);
            }
        }
    }

    // cout <<"going to base case - newPtr "<< (newPtr != NULL) << endl;

    // Base Case
    if (cur->isLeaf() || newPtr != NULL){
        // cout << "adding to a leaf node" << endl;
        if (cur->isTwoNode()){
            // insert the new item
            if (anItem > cur->getSmallItem())
                cur->setLargeItem(anItem);
            else{
                T temp = cur->getSmallItem();
                cur->setSmallItem(anItem);
                cur->setLargeItem(temp);
            }

            // joining the child if existed (can be separate fcn)
            if (newPtr){
                if (newPtr->getSmallItem() < cur->getSmallItem()){
                    // join to the left
                    
                } else if (newPtr->getSmallItem() < cur->getLargeItem()){
                    // join in the middle
                    TriNode<T>* tmp = cur->getMidChildPtr();
                    cur->setMidChildPtr(newPtr);
                    cur->setRightChildPtr(tmp);
                } else {
                    // join to teh right
                    cur->setRightChildPtr(newPtr);
                }
            }
                
            // cout << "added to two node\t small " << cur->getSmallItem() << "  large  " << cur->getLargeItem() <<endl;
            
            newPtr = NULL;
        } 
        else {
            // figure which node to be sent to parent
            if (anItem > cur->getLargeItem()){
                // send the large item to parent
                swapWithChild(cur, anItem, 'L');
            } 
            else if (anItem < cur->getSmallItem()){
                // send the small item to parent
                swapWithChild(cur, anItem, 'S');
            } // end if

            // split into two nodes
            TriNode<T>* separatedNode;
            splitNode(cur, separatedNode, newPtr);
            newPtr = separatedNode;
            cur->setRightChildPtr(NULL);

            // cout << "added to Three node\t small " << cur->getSmallItem() << "  large " << cur->getLargeItem() <<endl;
            // cout << "node sepatated\t" << newPtr->getSmallItem() << endl;

            if (root == cur){
                // cout << "adding item to new root"<< "\t";
                TriNode<T>* tmp = root;
                root = new TriNode<T>(anItem);
                root->setLeftChildPtr(tmp);
                root->setMidChildPtr(newPtr);
                // cout << "new root " << root->getSmallItem() << endl;
                return;
            }
        } // end if
    }
    return;
}

template <class T>
void Tree23<T>::swapWithChild(TriNode<T>* root, T &anItem, char which){
    T temp;

    switch (which)
    {
    case 'l':
    case 'L':
        temp = anItem;
        anItem = root->getLargeItem();
        root->setLargeItem(temp);
        break;
    
    case 's':
    case 'S':
        temp = anItem;
        anItem = root->getSmallItem();
        root->setSmallItem(temp);
        break;
    
    default:
        break;
    }
}

template <class T>
void Tree23<T>::splitNode(TriNode<T>* origNode, TriNode<T>* &separatedNode, TriNode<T>* newNode){
    separatedNode = new TriNode<T>();
    separatedNode->setSmallItem(origNode->getLargeItem());

    // Redistribute the children, including the one came from the 
    // separation of on of the children
    if (newNode){
        if (newNode->getSmallItem() < separatedNode->getSmallItem()){
            if (newNode->getSmallItem() < origNode->getMidChildPtr()->getSmallItem()){
                separatedNode->setLeftChildPtr(origNode->getMidChildPtr());
                separatedNode->setMidChildPtr(origNode->getRightChildPtr());

                origNode->setMidChildPtr(newNode);
                origNode->setRightChildPtr(NULL);
            } else {
                separatedNode->setLeftChildPtr(newNode);
                separatedNode->setMidChildPtr(origNode->getRightChildPtr());

                origNode->setMidChildPtr(origNode->getMidChildPtr());
                origNode->setRightChildPtr(NULL);
            }
        }
        else {
            separatedNode->setLeftChildPtr(origNode->getRightChildPtr());
            separatedNode->setMidChildPtr(newNode);

            origNode->setRightChildPtr(NULL);
        }
    }
}

template <class T>
bool Tree23<T>::remove(T anItem){
    return false;
}

template <class T>
string Tree23<T>::toTreeString(){
    string output = "";
    toTreeString(this->root, output);

    return output;
}

template <class T>
void Tree23<T>::toTreeString(TriNode<T>* root, string &output){
    std::ostringstream oss;

    // Base Case
    if (root->isLeaf()){
        // wrap its contents with {}
        oss << "{";
        oss << root->getSmallItem();
        if (root->isThreeNode()){
            oss << ",";
            oss << root->getLargeItem();
        }
        oss << "}";
        output += oss.str();
        oss.str("");
        oss.clear();
        return;
    }

    // Not a leaf
    // *** add self ***
    // Print Smaller Item
    oss << "{";
    oss << root->getSmallItem();
    // Print Larger Item
    if (root->isThreeNode()){
        oss << ",";
        oss << root->getLargeItem();
    }
    oss << "}";

    // add Left child
    oss << "(";
    output += oss.str();
    oss.str("");
    oss.clear();
    toTreeString(root->getLeftChildPtr(), output);

    // add Middle child
    oss << ",";
    output += oss.str();
    oss.str("");
    oss.clear();
    toTreeString(root->getMidChildPtr(), output);

    if (root->isThreeNode()) {
        // add right child
        oss << ",";
        output += oss.str();
        oss.str("");
        oss.clear();
        toTreeString(root->getRightChildPtr(), output);
    }

    oss << ")";
    output += oss.str();
    oss.str("");
    oss.clear();
}

template <class T>
void Tree23<T>::insert(TriNode<T> *child, TriNode<T> *parent){
    if (parent == NULL){
        root = child;
        return;
    }

    if (parent->getLeftChildPtr() == NULL){
        parent->setLeftChildPtr(child);
    } else if (parent->getMidChildPtr() == NULL) {
        parent->setMidChildPtr(child);
    } else if (parent->getRightChildPtr() == NULL){
        parent->setRightChildPtr(child);
    }
}

template <class T>
void Tree23<T>::constructFromTreeString(string treeString){
    stack<TriNode<T>*> parentsStack;
    TriNode<T>* tmpNode;
    int childCount = 0;

    for (int i = 0; i < treeString.length(); i++){
        switch (treeString.at(i))
        {
        case '{':
        tmpNode = new TriNode<T>();
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

// int main (){
//     Tree23<int>* node = new Tree23<int>();
//     node->insert(10);
//     node->insert(5);
//     node->insert(2);
//     node->insert(3);
//     node->insert(7);
//     node->insert(1);
//     node->traverse();
//     return 0;
// }

template class Tree23<int>;
template class Tree23<string>;