/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>
using namespace std;

class AVLTree {
public:
    using KeyType = std::string;
    using ValueType = size_t;
    size_t length;

    bool insert(const std::string& key, size_t value);
    bool remove(const std::string& key);
    bool contains(const std::string&) const;
    optional<size_t> get(const std::string&) const;
    size_t& operator[](const std::string& key);
    vector<size_t> findRange(const string& lowKey, const string& highKey) const;
    vector<std::string>keys() const;
    size_t size() const;
    size_t getHeight() const;
    AVLTree &operator=(const AVLTree& other);
    ~AVLTree();

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
    AVLTree() : root(nullptr), length(0){};

    bool recursion(AVLNode*& current,const std::string &key, size_t value);
    int height(AVLNode* Node);
    bool rotateRight(AVLNode*& node);
    bool rotateLeft(AVLNode*& node);
    friend std::ostream& operator<<(ostream& os, const AVLTree& avlTree);
    void printSubtree(AVLNode* node, int depth) const;
    void findRangeHelper(AVLNode* node,const string& lowKey, const string& highKey, vector<size_t> &result) const;
    vector<string> keysHelper(AVLNode* node, vector<string> &result) const;
    void deepCopyHelper(AVLNode *currentOld, AVLNode *&currentNew);
    AVLTree(const AVLTree& other);
    void clear(AVLNode*& node);
    AVLNode *searchNode(AVLNode *node, const std::string key) const;

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
