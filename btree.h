#ifndef BTREE_H
#define BTREE_H
#include "btreenode.h"
#include <iostream>
using namespace std;
class BTree
{
private:
    BTreeNode *root;
    int t;
public:

    BTree(int);
    void traverse();
    BTreeNode* search(int);
    void insert(int);
    void remove(int);
};

#endif // BTREE_H
