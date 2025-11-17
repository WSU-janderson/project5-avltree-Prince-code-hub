#include "AVLTree.h"

#include <iostream>
#include <string>



bool AVLTree::insert(const std::string &key, size_t value) {

    // if (root == nullptr) {
    //     root = new AVLNode();
    //     root->key = key;
    //     root->value = value;
    //     root->left = nullptr;
    //     root->right = nullptr;
    //     root->height = 0;
    //     return true;
    // }

    return recursion(root, key, value);
}

bool AVLTree::remove(const std::string &key) {
    return remove(root, key);
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

bool AVLTree::recursion(AVLNode *&current, const std::string &key, size_t value) {
    if (current == nullptr) {
        current = new AVLNode();
        current->key = key;
        current->value = value;
        current->left = nullptr;
        current->right = nullptr;
        current->height = 0;
        return true;
    }

    if (current->key == key) {
        return false;
    }

    bool inserted;

    if(key < current->key) {
       inserted = recursion(current->left, key, value);
    }else if (key > current->key) {
       inserted = recursion(current->right, key, value);
    }else {
        return false;
    }

    if (inserted) {
        current->height = 1 + max(height(current->left), height(current->right));
        balanceNode(current);
    }
    return inserted;
}

int AVLTree::height(AVLNode *Node){
    if (Node == nullptr) {
        return -1;
    }else {
        return Node->height;
    }
}

bool AVLTree::rotateRight(AVLNode *&node) {

    AVLNode *problem = node;
    AVLNode *hook = problem->left;
    AVLNode *middle = hook->right;


    node->left = middle;
    hook->right = node;
    node = hook;

    problem->height = 1 + max(height(problem->left), height(problem->right));
    hook->height = 1 + max(height(hook->left), height(hook->right));

    return true;

}

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

void AVLTree::printSubtree(AVLNode *node, int depth) const {


}

bool AVLTree::remove(AVLNode *&current, KeyType key) {

    if (current == nullptr) {
        return false;
    }

    bool removed;

    if(key < current->key) {
       removed =  remove(current->left, key);
    }else if (key > current->key) {
        removed =remove(current->right, key);
    }else {
            removed = removeNode(current);
        return removed;
    }



    if (removed) {
        current->height = 1 + max(height(current->left), height(current->right));
        balanceNode(current);
    }
    return removed;
}

void AVLTree::balanceNode(AVLNode *&node) {
    int leftHeight = 0;
    int rightHeight = 0;
    if (node->left == nullptr) {
        leftHeight = -1;
    }else{
        leftHeight = height(node->left);
    }

    if (node->right == nullptr) {
        rightHeight = -1;
    }else{
        rightHeight = height(node->right);
    }

    int balance = leftHeight - rightHeight;
    if (balance > 1) {
        int childBalance = height(node->left->left) - height(node->left->right);
         if (childBalance >= 0){
             rotateRight(node);
        }else {
            rotateLeft(node->left);
            rotateRight(node);
        }

    }
    if (balance < -1) {
        int childBalance = height(node->right->left) - height(node->right->right);
        if (childBalance <= 0){
            rotateLeft(node);
        }else {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }

}

std::ostream & operator<<(ostream &os, const AVLTree &avlTree) {

    if (avlTree.root == nullptr) {
        return os;
    }


    return os;

}
