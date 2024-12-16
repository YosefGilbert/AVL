#pragma once
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/*One such balanced tree is an AVL tree that maintains a threshold of 1. As soon as a
 node in an AVL tree has a balance factor of +2/-2, “tree rotations” are performed
 to maintain balance in the tree.*/

/* balance factor is defined:  The difference in heights of the left and right subtrees
 of any given node*/

/* On balancing:  I think it should be desired that the root be the median of the data set, and
 * that each node be the median of the subset of data in its subtree.  */


//used the template video for insight on the class structure
class Node {
public:
    //attributes
    string ID;
    string NAME;
    Node* successor;
    int height; //the height of the subtree that has the current node as its root
    int depth; // the level of a node relative to the actual root of the tree
    int balanceFactor;
    Node* left;
    Node* right;

    Node(string id, string name)
    {
        ID = id;
        NAME = name;
        left = nullptr;
        right = nullptr;
        height = 1;
        depth = 0;
        balanceFactor = 0;
        successor = nullptr;
    }
};

class Tree {

    Node* root = nullptr;
    Node* insert(Node *node, string ID, string name);
    void fixHeights(Node* child);
    int updateHeights(Node* node, string ID);
    Node* remove(Node* node, string ID);
    void inOrderVector(Node* node, vector<string>& names);
    void preOrderVector(Node* node, vector<string>& names);
    void postOrderVector(Node* node, vector<string>& names);
    Node* search(Node* node, string ID);
    void search(Node* node, string name, vector<string>& IDs);
    Node* leftRotate(Node* node);
    Node* rightRotate(Node* node);
    void printHeights(Node* node);
    void removeInorder(Node* node, int N);
    void destructorHelper(Node* node);
public:
    void insert(string ID, string name);
    void remove(string ID);
    string searchID(string ID);
    void searchName(string name);
    vector<string> printInorder();
    vector<string> printPreorder();
    vector<string> printPostorder();
    void printLevelCount();
    void removeInorder(int N);
    void printHeights();
    void printVector(vector<string>& vector);

    bool isBalanced = true;
    Tree();
    ~Tree();





};


