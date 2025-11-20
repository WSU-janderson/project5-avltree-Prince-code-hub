/*
Name: Prince Patel
Project: CS 3100 – AVL Trees
File: AVLTree.cpp

Description :- This file has implemented AVL tree. There is insertation, remove, find range, balance, height and rotation as main functions. There are other functions as well.
*/
#include "AVLTree.h"


#include <iostream>
#include <string>


//insert key, value pair into avl tree
bool AVLTree::insert(const std::string &key, size_t value) {
    return recursion(root, key, value);
}

//remove node with key from the tree
bool AVLTree::remove(const std::string &key) {
    return remove(root, key);
}

//check a key exists in the tree or not
bool AVLTree::contains(const std::string &key) const {
    AVLNode *contains = searchNode(root, key);
    if (contains == nullptr) {
        return false;
    } else {
        return true;
    }
}

//return number of children of node
size_t AVLTree::AVLNode::numChildren() const {
    if (left == nullptr && right == nullptr) {
        return 0;
    } else if (left != nullptr && right != nullptr) {
        return 2;
    } else {
        return 1;
    }
}

//check node has children or not
bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    } else {
        return false;
    }
}

//return height of node
size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

//code given by professor, it just removes specific node
bool AVLTree::removeNode(AVLNode *&current) {
    if (!current) {
        return false;
    }

    AVLNode *toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode *smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

//recursion that made for insert
bool AVLTree::recursion(AVLNode *&current, const std::string &key, size_t value) {
    //makes new node when current is nullptr
    if (current == nullptr) {
        current = new AVLNode();
        current->key = key;
        current->value = value;
        current->left = nullptr;
        current->right = nullptr;
        current->height = 0;
        length++;
        return true;
    }
    //for duplication check
    if (current->key == key) {
        return false;
    }
    //to check insert happened or not
    bool inserted;


    // Recursive call to find space to insert new node
    if (key < current->key) {
        inserted = recursion(current->left, key, value);
    } else if (key > current->key) {
        inserted = recursion(current->right, key, value);
    } else {
        return false;
    }

    //if insert happened then update height and balance
    if (inserted) {
        current->height = 1 + max(height(current->left), height(current->right));
        balanceNode(current);
    }
    return inserted;
}
//height function for height
int AVLTree::height(AVLNode *Node) {
    if (Node == nullptr) {
        return -1;
    } else {
        return Node->height;
    }
}
//right rotation
bool AVLTree::rotateRight(AVLNode *&node) {
    AVLNode *problem = node;
    AVLNode *hook = problem->left;
    AVLNode *middle = hook->right;


    problem->left = middle;
    hook->right = problem;
    node = hook;

    problem->height = 1 + max(height(problem->left), height(problem->right));
    hook->height = 1 + max(height(hook->left), height(hook->right));

    return true;
}
//left rotation
bool AVLTree::rotateLeft(AVLNode *&node) {
    AVLNode *problem = node;
    AVLNode *hook = problem->right;
    AVLNode *middle = hook->left;


    problem->right = middle;
    hook->left = problem;
    node = hook;

    problem->height = 1 + max(height(problem->left), height(problem->right));
    hook->height = 1 + max(height(hook->left), height(hook->right));


    return true;
}
// function to print tree
void AVLTree::printSubtree(AVLNode *node, int depth) const {
    if (node == nullptr) {
        return;
    }

    printSubtree(node->right, depth + 1);
    for (int i = 0; i < depth; i++) {
        cout << "  ";
    }
    std::cout << node->key << ": " << node->value << endl;
    printSubtree(node->left, depth + 1);
}
//helper function to find range
void AVLTree::findRangeHelper(AVLNode *node, const string &lowKey, const string &highKey,
                              vector<size_t> &result) const {
    if (node == nullptr) {
        return;
    }
    if (node->key > lowKey) {
        findRangeHelper(node->left, lowKey, highKey, result);
    }
    if (node->key >= lowKey && node->key <= highKey) {
        result.push_back(node->value);
    }
    if (node->key < highKey) {
        findRangeHelper(node->right, lowKey, highKey, result);
    }
}
//helper function to find stored key
vector<string> AVLTree::keysHelper(AVLNode *node, vector<string> &result) const {
    if (node == nullptr) {
        return result;
    }

    keysHelper(node->left, result);
    result.push_back(node->key);
    keysHelper(node->right, result);

    return result;
}
//helper function for deep copy
void AVLTree::deepCopyHelper(AVLNode *currentOld, AVLNode *&currentNew) {
    if (currentOld == nullptr) {
        currentNew = nullptr;
        return;
    }

    currentNew = new AVLNode();
    currentNew->key = currentOld->key;
    currentNew->value = currentOld->value;
    currentNew->height = currentOld->height;

    deepCopyHelper(currentOld->left, currentNew->left);
    deepCopyHelper(currentOld->right, currentNew->right);
}
//copy function for deep copy
AVLTree::AVLTree(const AVLTree &other) {
    root = nullptr;
    length = other.length;

    deepCopyHelper(other.root, root);
}
//function for get
optional<size_t> AVLTree::get(const std::string &key) const {
    AVLNode *getValue = searchNode(root, key);

    if (getValue == nullptr) {
        return 0;
    } else {
        return getValue->value;
    }
}
//operator function
size_t &AVLTree::operator[](const std::string &key) {
    AVLNode *node = searchNode(root, key);

    if (node == nullptr) {
        throw std::runtime_error("Key not found");
    }

    return node->value;
}
// range function
vector<size_t> AVLTree::findRange(const string &lowKey, const string &highKey) const {
    vector<size_t> result;
    findRangeHelper(root, lowKey, highKey, result);
    return result;
}
// function for finding keys
vector<std::string> AVLTree::keys() const {
    vector<string> result;
    result = keysHelper(root, result);
    return result;
}
//function for size
size_t AVLTree::size() const {
    return length;
}
//function for height
size_t AVLTree::getHeight() const {
    if (root == nullptr) {
        return 0;
    }
    return root->height;
}
//assignment operator for deep copy
AVLTree &AVLTree::operator=(const AVLTree &other) {
    clear(root);

    root = nullptr;
    length = 0;
    deepCopyHelper(other.root, root);
    length = other.length;

    return *this;
}
// function to clear all nodes
void AVLTree::clear(AVLNode *&node) {
    if (node == nullptr) {
        return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
    node = nullptr;
}
//destructer
AVLTree::~AVLTree() {
    clear(root);
}
//helper function for get and operator
AVLTree::AVLNode *AVLTree::searchNode(AVLNode *node, const std::string key) const {
    if (node == nullptr) {
        return node;
    }
    if (node->key == key) {
        return node;
    }
    if (key < node->key) {
        return searchNode(node->left, key);
    } else if (key > node->key) {
        return searchNode(node->right, key);
    }
    return nullptr;
}
//remove function that removes node
bool AVLTree::remove(AVLNode *&current, KeyType key) {
    if (current == nullptr) {
        return false;
    }

    bool removed;

    if (key < current->key) {
        removed = remove(current->left, key);
    } else if (key > current->key) {
        removed = remove(current->right, key);
    } else {
        removed = removeNode(current);
        length--;
        return removed;
    }
    if (removed) {
        current->height = 1 + max(height(current->left), height(current->right));
        balanceNode(current);
    }
    return removed;
}
//function to check balance
void AVLTree::balanceNode(AVLNode *&node) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (node->left == nullptr) {
        leftHeight = -1;
    } else {
        leftHeight = height(node->left);
    }

    if (node->right == nullptr) {
        rightHeight = -1;
    } else {
        rightHeight = height(node->right);
    }

    int balance = leftHeight - rightHeight;
    if (balance > 1) {
        int childBalance = height(node->left->left) - height(node->left->right);
        if (childBalance >= 0) {
            rotateRight(node);
        } else {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    if (balance < -1) {
        int childBalance = height(node->right->left) - height(node->right->right);
        if (childBalance <= 0) {
            rotateLeft(node);
        } else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}
//friend function that actually prints tree using printSubTree
std::ostream &operator<<(ostream &os, const AVLTree &avlTree) {
    avlTree.printSubtree(avlTree.root, 0);

    return os;
}
