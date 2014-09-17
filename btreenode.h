#ifndef BTREENODE_H
#define BTREENODE_H
#include <iostream>
using namespace std;
class BTreeNode
{
private:

public:
    int *keys;
    int t;
    BTreeNode **C;
    int n;
    bool leaf;
   BTreeNode(int, bool);
   void traverse();
   void insertNonFull(int);
   void splitChild(int, BTreeNode*);
   BTreeNode* search(int);
   void merge(int);
   void borrowFromNext(int);
   void borrowFromPrev(int);
   void remove(int);
   void removeFromLeaf (int);
   void removeFromNonLeaf(int);
   int getPred(int);
   int getSucc(int);
   void fill(int);
   int findKey(int);

};

#endif // BTREENODE_H
