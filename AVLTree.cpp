#include "AVLTree.h"

#include <string>

bool AVLTree::insert(const std::string &key, size_t value) {
    if (root == nullptr) {
        root = new AVLNode();
        root->key = key;
        root->value = value;
        root->left = nullptr;
        root->right = nullptr;
        root->height = 0;
        return true;
    }
    AVLNode *&insertPos = recursion(root, key, value);

    if (insertPos != nullptr) {
        return false;
    }
    insertPos = new AVLNode();
    insertPos->key = key;
    insertPos->value = value;
    insertPos->left = nullptr;
    insertPos->right = nullptr;
    insertPos->height = 0;



    return true;
}


size_t AVLTree::AVLNode::numChildren() const {
    if (left == nullptr && right == nullptr) {
        return 0;
    } else if (left != nullptr && right != nullptr) {
        return 2;
    } else {
        return 1;
    }
}

bool AVLTree::AVLNode::isLeaf() const {
    if (left == nullptr && right == nullptr) {
        return true;
    } else {
        return false;
    }
}

size_t AVLTree::AVLNode::getHeight() const {
    return height;
}

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

AVLTree::AVLNode *&AVLTree::recursion(AVLNode *&current, const std::string &key, size_t value) {
    if (current == nullptr) {
        return current;
    }
    if (current->key == key) {
        return current;
    }
    if (key < current->key) {
        return recursion(current->left, key, value);
    }
    if (key > current->key) {
        return recursion(current->right, key, value);
    }
}

int AVLTree::getHeight(AVLNode *node) {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {
}
