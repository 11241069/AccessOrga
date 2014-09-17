#include "btree.h"


BTree::BTree(int _t)
{
    root=NULL;
    t = _t;
}
void BTree::traverse()
{
    if (root != NULL)
        root->traverse();
}
BTreeNode* BTree::search(int k)
{
    return (root == NULL)? NULL : root->search(k);
}
void BTree::insert(int k)
{
    if (root == NULL)
    {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else
    {
        if (root->n == (t*2)-1)
        {
            BTreeNode *s = new BTreeNode(t, false);
            s->C[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->C[i]->insertNonFull(k);
            root = s;
        }
        else
            root->insertNonFull(k);
    }
}
void BTree::remove(int k)
{
    if (!root)
    {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(k);


    if (root->n==0)
    {
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            root = root->C[0];


        delete tmp;
    }
    return;
}
