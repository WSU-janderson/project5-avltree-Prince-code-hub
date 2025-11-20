/*
Driver code for testing your AVL Tree
This is NOT the test code for grading,
instead for you to get an idea of how to test the tree
 */
#include "AVLTree.h"
#include <iostream>
#include <string>
#include <ranges>
#include <vector>
using namespace std;

void foo() {
    AVLTree tree;
    tree.insert("B", 'B');
    tree.insert("K", 'K');
    tree.insert("F", 'F');
    tree.insert("N", 'N');
    tree.insert("C", 'C');
    tree.insert("M", 'M');
    tree.insert("L", 'L');
    tree.insert("R", 'R');
}


int main() {
    bool insertResult;
    bool removeResult;
    AVLTree tree;
    // insertResult = tree.insert("F", 'F');
    // cout << insertResult << endl;
//
    system("pause");
    for (int i = 0; i < 10000; i++) {
        foo();
    }
    system("pause");
 // cout << insertResult << endl;

    insertResult = tree.insert("A", 'A');
    cout << insertResult << endl;
    insertResult= tree.insert("A", 'A');
    cout << insertResult << endl;


    tree.insert("B", 'B');
    tree.insert("K", 'K');
    tree.insert("F", 'F');
    tree.insert("N", 'N');

    tree.insert("G", 'G');
    cout << tree << endl;

    AVLTree tree2 = tree;

    cout << tree2 << endl;

    tree.insert("C", 'C');
    cout << tree << endl;
    cout << tree2 << endl;

     // int a =  tree.size();
//     // cout << a << endl;
//
//     cout << tree << endl;
//
//
//
//     insertResult = tree.insert("B", 'B'); // false, no duplicates allowed
//     cout << insertResult << endl;
//     insertResult = tree.insert("C", 'C'); // false, no duplicates allowed
//     cout << insertResult << endl;
//     insertResult = tree.insert("A", 'A'); // false, no duplicates allowed
//     cout << insertResult << endl;
//     insertResult = tree.insert("F", 'F');
//     cout << insertResult << endl;
//     insertResult = tree.insert("G", 'G');
//     cout << insertResult << endl;
//     removeResult = tree.remove("G");
// cout << removeResult << endl;
//
//
//     insertResult = tree.insert("K", 'K');
//     insertResult = tree.insert("X", 'X');// single rotate left
//     cout << endl << endl;
//     cout << tree << endl;
//
//     insertResult = tree.insert("C", 'C');
//     insertResult = tree.insert("A", 'A'); // single rotate right
//     cout << endl << endl;
//     cout << tree << endl;
//
//     insertResult = tree.insert("D", 'D'); // double rotate right
//     cout << endl << endl;
//     cout << tree << endl;
//
//     insertResult = tree.insert("R", 'R'); // double rotate left
//     cout << endl << endl;
//     cout << tree << endl;
//
//     insertResult = tree.insert("V", 'V');
//     insertResult = tree.insert("A", 'A'); // false, duplicate
//     insertResult = tree.insert("Z", 'Z');
//     insertResult = tree.insert("M", 'M');
//     insertResult = tree.insert("D", 'D'); // false, duplicate
//     cout << endl << endl;
//     cout << tree << endl;
//     //
//     // // size and getHeight
//     cout << "tree size: " << tree.size() << endl; // 10
//     cout << "tree height: " << tree.getHeight() << endl; // 3
//     cout << endl;
// //
// //    // contains
//      bool containsResult;
//      containsResult = tree.contains("A"); // true
//      cout << containsResult << endl;
//      containsResult = tree.contains("N"); // false
//      cout << containsResult << endl;
// //
// // //
// // //    // get
//      optional<int> getResult;
//
//      getResult = tree.get("A"); // 65
//      cout << "A: " << getResult.value() << endl;
//
//      getResult = tree.get("C"); // 67
//      cout << "C: " << getResult.value() << endl;
//
//      getResult = tree.get("Q"); // getResult has no value
//      cout << "Q: " << getResult.value() << endl; // print 0
//      cout << endl;
// // //
//     // findRange
//     vector<size_t> rangeTest = tree.findRange("D","W");
//     // 70 68 82 75 77 86
//     for (auto val: rangeTest) {
//         cout << val << " ";
//     }
//     cout << endl << endl;
// //
// // //    // operator[]
//      tree["A"] = 108;
//      cout << tree << endl;
//      cout << endl;
//
//    // remove
//     removeResult= tree.remove("A"); // "A" is a leaf
//     cout << endl << endl;
//     cout << tree << endl;
//
//     removeResult = tree.remove("C"); // "C" has one child, single rotate left
//     cout << endl << endl;
//     cout << tree << endl;
//
//    removeResult = tree.remove("F"); // "F" has two children
//    cout << endl << endl;
//    cout << tree << endl;
//
//    removeResult = tree.remove("V");
//    removeResult = tree.remove("X");
//    removeResult = tree.remove("Z"); // double rotate right
//    cout << endl << endl;
//    cout << tree << endl;
//
    return 0;
}
