#include "binarysearchtree.h"
template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const Comparable &notFound) : ITEM_NOT_FOUND(notFound)
{
    root = nullptr;
}

template <class Comparable>
BinarySearchTree<Comparable>::BinarySearchTree(const BinarySearchTree &rhs) : ITEM_NOT_FOUND(rhs.ITEM_NOT_FOUND)
{
    root = rhs.root;
}

template <class Comparable>
const BinarySearchTree<Comparable> &BinarySearchTree<Comparable>::operator=(const BinarySearchTree<Comparable> &rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::clone(BinaryNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode<Comparable>(t->element, clone(t->left), clone(t->right));
}

template <class Comparable>
BinarySearchTree<Comparable>::~BinarySearchTree()
{
    makeEmpty();
}

template <class Comparable>
bool BinarySearchTree<Comparable>::findSymbol(char ch) const
{
    if (!root)
        return false;
    if (hasSymbol(root, ch))
        return true;
    else if (hasSymbol(root->left, ch))
        return true;
    return hasSymbol(root->right, ch);
}

template <class Comparable>
bool BinarySearchTree<Comparable>::hasSymbol(BinaryNode<Comparable> *t, char ch) const
{
    if (!t)
        return false;
    else if (t->element.symbol == ch)
        return true;
    else
    {
        if (hasSymbol(t->left, ch))
            return true;
        return hasSymbol(t->right, ch);
    }
}

template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::find(const Fileinfo<int> &f) const
{
    return elementAt(find(f, root));
}

template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::elementAt(BinaryNode<Comparable> *t) const
{
    return t == nullptr ? ITEM_NOT_FOUND : t->element;
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::find(const Fileinfo<int> &f, BinaryNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    else if (f.frequency < t->element.frequency)
        return find(f, t->left);
    else if (t->element.frequency < f.frequency)
        return find(f, t->right);
    else
        return t; //Match
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMin(BinaryNode<Comparable> *t) const
{ //Recursive implementation
    if (t == nullptr)
        return nullptr;
    if (t->left == nullptr)
        return t;
    return findMin(t->left);
}

template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::findMin() const
{
    return findMin(root)->element;
}

template <class Comparable>
BinaryNode<Comparable> *BinarySearchTree<Comparable>::findMax(BinaryNode<Comparable> *t) const
{ //Non recursive implementation
    if (t != nullptr)
        while (t->right != nullptr)
            t = t->right;
    return t;
}

template <class Comparable>
const Comparable &BinarySearchTree<Comparable>::findMax() const
{
    return findMax(root)->element;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::isEmpty() const
{
    return root == nullptr;
}
template <class Comparable>
int BinarySearchTree<Comparable>::depth()
{
    total = 0;
    depth(root->left);
    depth(root->right);
    return total;
}

template <class Comparable>
void BinarySearchTree<Comparable>::depth(BinaryNode<Comparable> *t)
{
    if (t == nullptr)
        return;
    else
    {
        total += 1;
        depth(t->left);
        depth(t->right);
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const
{
    if (t == nullptr)
        t = new BinaryNode<Comparable>(f, nullptr, nullptr);
    else if (f.frequency < t->element.frequency)
        insert(f, t->left);
    else if (t->element.frequency < f.frequency)
        insert(f, t->right);
    else
        insert(f, t->left);
}

template <class Comparable>
void BinarySearchTree<Comparable>::insert(const Fileinfo<int> &f)
{
    insert(f, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::insertLeft(const BinarySearchTree *rhs)
{
    root->left = rhs->root;
}

template <class Comparable>
void BinarySearchTree<Comparable>::insertRight(const BinarySearchTree *rhs)
{
    root->right = rhs->root;
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const
{
    if (t == nullptr)
        return;
    if (f.frequency < t->element.frequency)
        remove(f, t->left);
    else if (t->element.frequency < f.frequency)
        remove(f, t->right);
    else if (t->left != nullptr && t->right != nullptr)
    {
        t->element = findMin(t->right)->element;
        remove(f, t->right);
    }
    else
    {
        BinaryNode<Comparable> *oldNode = t;
        t = t->left != nullptr ? t->left : t->right;
        delete oldNode;
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::remove(const Fileinfo<int> &f)
{
    remove(f, root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty(BinaryNode<Comparable> *&t) const
{
    if (t != nullptr)
    {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template <class Comparable>
void BinarySearchTree<Comparable>::makeEmpty()
{
    makeEmpty(root);
}

template <class Comparable>
void BinarySearchTree<Comparable>::preOrder(BinaryNode<Comparable> *t) const
{
    if (t == nullptr)
        return;
    else
    {
        cout << t->element.symbol << ":" << t->element.frequency << " ";
        preOrder(t->left);
        preOrder(t->right);
    }
}

template <class Comparable>
void BinarySearchTree<Comparable>::print() const
{
    if (!root)
        return;
    cout << root->element.symbol << ":" << root->element.frequency << " ";
    preOrder(root->left);
    preOrder(root->right);
}

template <class Comparable>
int BinarySearchTree<Comparable>::getFrequency() const
{
    return this->root->element.frequency;
}

template <class Comparable>
void BinarySearchTree<Comparable>::flag()
{
    this->root->element.flag = true;
}

template <class Comparable>
bool BinarySearchTree<Comparable>::flagged() const
{
    return this->root->element.flag;
}

template class BinarySearchTree<Fileinfo<int>>;