/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <string>

using namespace std;

class AVLTree {
public:
    // AVLTree();

    using KeyType = std::string;
    using ValueType = size_t;

    bool insert(const std::string& key, size_t value);
    bool remove(const std::string& key);


protected:
    class AVLNode {
    public:

        KeyType key;
        ValueType value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;


    };

public:




    private:
    AVLNode* root;

public:
    AVLTree() : root(nullptr) {};

    bool recursion(AVLNode*& current,const std::string &key, size_t value);
    int height(AVLNode* Node);
    bool rotateRight(AVLNode*& node);
    bool rotateLeft(AVLNode*& node);
    friend std::ostream& operator<<(ostream& os, const AVLTree& avlTree);
    void printSubtree(AVLNode* node, int depth) const;






private:

    /* Helper methods for remove */
    // this overloaded remove will do the recursion to remove the node
    bool remove(AVLNode*& current, KeyType key);
    // removeNode contains the logic for actually removing a node based on the numebr of children
    bool removeNode(AVLNode*& current);
    // You will implement this, but it is needed for removeNode()
    void balanceNode(AVLNode*& node);

};

#endif //AVLTREE_H
