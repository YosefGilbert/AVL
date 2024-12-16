// this method inserts a node using double pointers
#include "AVL.h"
#include <vector>



//--------------------------- PRIVATE FUNCTIONS --------------------------- //
// the following are functions of the root node and other data the user cannot access

// from module 5 AVL insert
Node *Tree::insert(Node *node, string ID, string name)
{
    if (node == nullptr){
        return new Node(ID, name);
    }
    if (stoi(ID) < stoi(node->ID))
    {
        node->left = insert(node->left, ID, name);
    }
    if (stoi(ID) > stoi(node->ID))
    {
        node->right = insert(node->right, ID, name);
    }
    //Update heights
    node->height = 1 + max(node->left ? node->left->height : 0, node->right ? node->right->height : 0);

    //RIGHT HEAVY
    if ((node->left ? node->left->height : 0) + 1 < (node->right ? node->right->height : 0)){
        // RIGHT SUBTREE IS LEFT HEAVY
        if ((node->right->left ? node->right->left->height : 0) > (node->right->right ? node->right->right->height : 0)){
            node->right = rightRotate(node->right);
            node = leftRotate(node);
        }else{
            node = leftRotate(node);
        }
    }else{
        //LEFT HEAVY
        if ((node->right ? node->right->height : 0) + 1 < (node->left ? node->left->height : 0))
        {
            //LEFT SUBTREE IS RIGHT HEAVY
            if ((node->left->right ? node->left->right->height : 0) > (node->left->left ? node->left->left->height : 0))
            {
                node->left = leftRotate(node->left);
                node = rightRotate(node);
            }else{
                node = rightRotate(node);
            }
        }
    }
    return node;
}

void Tree::printVector(vector<string>& vector)  // O(n), n being the vector size; this function is used in the traversals which are already O(n)
{
    if (!vector.empty()){
        for (unsigned int i = 0; i < vector.size() - 1; i++)
        {
            cout << vector[i] << ", ";
        }
        cout << vector[vector.size() - 1] << endl;
    }
}

// from module 5
Node* Tree::leftRotate(Node* node) // O(1)
{
    Node* grandchild = node->right->left;
    Node* newParent = node->right;
    newParent->left = node;
    node->right = grandchild;
    fixHeights(newParent);
    return newParent;
}

Node* Tree::rightRotate(Node* node) // O(1)
{
    Node* grandchild = node->left->right;
    Node* newParent = node->left;
    newParent->right = node;
    node->left = grandchild;
    fixHeights(newParent);
    return newParent;
}

void Tree::fixHeights(Node *child)  // O(1), only touches a maximum of 7 nodes
{
    if (child->left != nullptr){
        child->left->height = max(child->left->left ? child->left->left->height : 0, child->left->right? child->left->right->height : 0) + 1;
    }
    if (child->right != nullptr){
        child->right->height = max(child->right->left ? child->right->left->height : 0, child->right->right ? child->right->right->height: 0) + 1;
    }
    child->height = max(child->left ? child->left->height: 0, child->right ? child->right->height : 0) + 1;
}

void Tree::inOrderVector(Node* node, vector<string>& names) // O(n), takes in a vector and fills it with tree nodes InOrder
{
    if (node == nullptr)
    {
        return;
    }
    inOrderVector(node->left, names);
    names.push_back(node->NAME);
    inOrderVector(node->right, names);
}

void Tree::preOrderVector(Node* node, vector<string> &names) // O(n), takes in a vector and fills it with tree nodes PreOrder
{
    if (node == nullptr)
    {
        return;
    }
    names.push_back(node->NAME);
    preOrderVector(node->left, names);
    preOrderVector(node->right, names);
}

void Tree::postOrderVector(Node* node, vector<string> &names) // O(n), takes in a vector and fills it with tree nodes PostOrder
{
    if (node == nullptr)
    {
        return;
    }
    postOrderVector(node->left, names);
    postOrderVector(node->right, names);
    names.push_back(node->NAME);
}

Node* Tree::search(Node* node, string ID) // O(log n), Assuming the tree is balanced, search space is (roughly)cut in half with each recursive call
{
    if (node == nullptr)    //indicates that the search was unsuccessful
    {
        return nullptr;
    }
    if (node->ID == ID){
        return node;
    }
    if (stoi(ID) < stoi(node->ID)){
        return search(node->left, ID);
    }
    if (stoi(ID) > stoi(node->ID)){
        return search(node->right, ID);
    }
    return nullptr;
}

void Tree::search(Node *node, string name, vector<string>& IDs) // O(n), performs a search through PreOrder traversal
{
    if (node == nullptr)
    {
        return;
    }
    if (node->NAME == name){
        IDs.push_back(node->ID);
    }
    search(node->left, name, IDs);
    search(node->right, name, IDs);
}


/*This method is O(log n), where n is the amount of nodes in the tree.  It first searches for the node to remove, which is O(log n) for
 * AVL trees.  Once found, the function does constant time operations in the cases where the node has children,
 * then updates the height(which is O(log n) as well), then removes.   */
Node* Tree::remove(Node *node, string ID)
{
    if (node == nullptr)
    {
        cout << "unsuccessful" << endl;
        return nullptr;
    }
    if (stoi(ID) < stoi(node->ID)){
        node->left = remove(node->left, ID);
    }
    if (stoi(ID) > stoi(node->ID)){
        node->right = remove(node->right, ID);
    }
    if (node->ID == ID)
    {
        if(node->left == nullptr)
        {
            if (node->right == nullptr)
            {
                // no children case
                updateHeights(root, node->ID);
                delete node;
                node = nullptr;
                cout << "successful" << endl;
            }
            else{
                // one child (right)
                updateHeights(root, node->right->ID);
                node->ID = node->right->ID;
                node->NAME = node->right->NAME;
                delete node->right;
                node->right = nullptr;
                cout << "successful" << endl;
            }
        }
        else{
            if (node->right == nullptr)
            {
                // one child (left)
                updateHeights(root, node->left->ID);
                node->ID = node->left->ID;
                node->NAME = node->left->NAME;
                delete node->left;
                node->left = nullptr;
                cout << "successful" << endl;
            }
            else{
                // two child case
                //finds the inorder successor
                Node** inorderSuccessor = &(node->right);
                while (true)
                {
                    if ((*inorderSuccessor)->left != nullptr){
                        inorderSuccessor = &(*inorderSuccessor)->left;
                    }
                    else{break;
                    }
                }
                updateHeights(root, (*inorderSuccessor)->ID);
                node->ID = (*inorderSuccessor)->ID;
                node->NAME = (*inorderSuccessor)->NAME;
                if ((*inorderSuccessor)->right != nullptr)
                {
                    delete (*inorderSuccessor);
                    (*inorderSuccessor) = (*inorderSuccessor)->right;
                }else{
                    delete (*inorderSuccessor);
                    (*inorderSuccessor) = nullptr;
                }
                cout << "successful" << endl;
            }
        }
    }
    return node;
}


/* This method of updating heights after a removal requires iterating over each of the deleted node's ancestors again.
 * While perhaps not the optimal solution, it only increases the time complexity by a constant multiple
 * Height is recalculated for each ancestor of the deleted node, but the heights of non-ancestor nodes are not recalculated,
 * leading to a time complexity of O(d), where d is the depth of the removed node.  In the worst case, d = log n + 1,
 * where n is the amount of nodes in the tree
 * so the time complexity is O(log n)
*/
int Tree::updateHeights(Node* node, string ID)
{
    if (node == nullptr)
    {
        return 0;
    }
    if (node->ID == ID)
    {
        node->height = 0;
        return node->height;
    }
    if (stoi(ID) < stoi(node->ID)){
        node->height = 1 + max(node->right ? node->right->height : 0, updateHeights(node->left, ID));
    }
    if (stoi(ID) > stoi(node->ID)){
        node->height = 1 + max(node->left ? node->left->height : 0, updateHeights(node->right, ID));
    }
    return 0;
}

void Tree::removeInorder(Node* node, int N) {
    if (node == nullptr){
        return;
    }
    removeInorder(node->left, N);
    N--;
    if(N == 0){
        root = remove(root, node->ID);
        return;
    }
    removeInorder(node->right, N);
}
// Constructor
Tree::Tree()
{
    root = nullptr;
}

//--------------------------- PUBLIC FUNCTIONS --------------------------- //
// the following are functions that take in user input and run private functions with data the user cannot access
// each public function's time complexity in O() is the same as its analogous private function (if applicable)

void Tree::insert(string ID, string name)
{
    root = insert(root, ID, name);
}

void Tree::remove(string ID)
{
    root = remove(root, ID);
}

string Tree::searchID(string ID)
{
    Node* node = search(root, ID);
    if (node != nullptr)
    {
        return node->NAME;
    }else{
        return "";
    }
}

void Tree::searchName(string name)
{
    vector<string> IDs;
    search(root, name, IDs);
    if (IDs.empty()){
        cout << "unsuccessful" << endl;
        return;
    }
    for (unsigned int i = 0; i < IDs.size(); i++)
    {
        cout << IDs[i] << endl;
    }
}

vector<string> Tree::printInorder()
{
    vector<string> names;
    inOrderVector(root, names);
    return names;
}

vector<string> Tree::printPreorder()
{
    vector<string> names;
    preOrderVector(root, names);
    return names;
}

vector<string> Tree::printPostorder()
{
    vector<string> names;
    postOrderVector(root, names);
    return names;
}

// O(1), this function only touches one node
void Tree::printLevelCount()
{
    cout << root->height << endl;
}

void Tree::removeInorder(int N) {
    removeInorder(root, N);
}

//destroys memory PostOrder, so as to end on the root node
Tree::~Tree() {
    destructorHelper(root);
}

void Tree::destructorHelper(Node *node) {
    if (node == nullptr)
    {
        return;
    }
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}
