#include "btree.h"
template <class Comparable>
BTree<Comparable>::BTree() { root = nullptr; }

template <class Comparable>
BTree<Comparable>::BTree(const BTree &rhs) { root = rhs.root; }

template <class Comparable>
BTree<Comparable>::~BTree()
{ /*makeEmpty();*/
}

template <class Comparable>
bool BTree<Comparable>::isEmpty() const { return root == nullptr; }

template <class Comparable>
void BTree<Comparable>::insert(const Fileinfo<int> &f) { insert(f, root); }

template <class Comparable>
void BTree<Comparable>::insertLeft(const BTree &rhs) { root->left = rhs.root; }

template <class Comparable>
void BTree<Comparable>::insertRight(const BTree &rhs) { root->right = rhs.root; }

template <class Comparable>
int BTree<Comparable>::getFrequency() const { return this->root->element.frequency; }

template <class Comparable>
void BTree<Comparable>::flag() { this->root->element.flag = true; }

template <class Comparable>
bool BTree<Comparable>::flagged() const { return this->root->element.flag; }

template <class Comparable>
char BTree<Comparable>::_symbol() const { return c; }

template <class Comparable>
void BTree<Comparable>::_rcurrentNode() { currentNode = root; }

template <class Comparable>
int BTree<Comparable>::len() const { return size; }

template <class Comparable>
const BTree<Comparable> &BTree<Comparable>::operator=(const BTree<Comparable> &rhs)
{
    if (this != &rhs)
    {
        //makeEmpty();
        root = clone(rhs.root);
    }
    return *this;
}

template <class Comparable>
BinaryNode<Comparable> *BTree<Comparable>::clone(BinaryNode<Comparable> *t) const
{
    if (t == nullptr)
        return nullptr;
    else
        return new BinaryNode<Comparable>(t->element, clone(t->left), clone(t->right));
}

template <class Comparable>
bool BTree<Comparable>::findSymbol(char ch) const { return root->element.symbol == ch; }

template <class Comparable>
int BTree<Comparable>::depth()
{
    count = 0;
    depth(root->left);
    depth(root->right);
    return count;
}

template <class Comparable>
void BTree<Comparable>::depth(BinaryNode<Comparable> *t)
{
    if (t == nullptr)
        return;
    else
    {
        count += 1;
        depth(t->left);
        depth(t->right);
    }
}

template <class Comparable>
void BTree<Comparable>::insert(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const
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
void BTree<Comparable>::preOrder(BinaryNode<Comparable> *t) const
{
    if (t == nullptr)
        return;
    else
    {
        std::cout << t->element.symbol << ":" << t->element.frequency << " ";
        preOrder(t->left);
        preOrder(t->right);
    }
}

template <class Comparable>
void BTree<Comparable>::print() const
{
    if (!root)
        return;
    std::cout << root->element.symbol << ":" << root->element.frequency << " ";
    preOrder(root->left);
    preOrder(root->right);
}

template <class Comparable>
Huffman *BTree<Comparable>::huffman(const int s)
{
    s ? size = s : true;
    Scode = "";
    count = 0;
    hf = new Huffman[size];
    if (!root)
        return hf;
    Scode.append("0");
    recordWeights(root->left);
    _switch();
    recordWeights(root->right);
    return hf;
}

template <class Comparable>
void BTree<Comparable>::recordWeights(BinaryNode<Comparable> *t)
{
    if (!t->left && !t->right)
    {
        hf[count].setData(t->element.symbol, Scode);
        t->element.code = Scode;
        count++;
        return;
    }
    else
    {
        Scode.append("0");
        recordWeights(t->left);
        _switch();
        recordWeights(t->right);
        popBack();
    }
}

template <class Comparable>
void BTree<Comparable>::popBack()
{
    if (Scode.length())
        Scode.pop_back();
}

template <class Comparable>
void BTree<Comparable>::_switch()
{
    popBack();
    Scode.append("1");
}
template <class Comparable>
std::string BTree<Comparable>::getTree()
{
    Scode = "";
    if (root)
    {
        Scode.append("0");
        appendToTree(root->left);
        appendToTree(root->right);
    }
    return Scode;
}

template <class Comparable>
void BTree<Comparable>::appendToTree(BinaryNode<Comparable> *t)
{
    if (!t->left && !t->right)
    {
        Scode.append("1" + std::string(1, t->element.symbol));
        return;
    }
    Scode.append("0");
    appendToTree(t->left);
    appendToTree(t->right);
}

template <class Comparable>
void BTree<Comparable>::mapTree(std::string tree)
{
    Scode = tree;
    insert(getInfo());
    count++;
    mapToChildren(root->left);
    mapToChildren(root->right);
}
template <class Comparable>
void BTree<Comparable>::mapToChildren(BinaryNode<Comparable> *&t)
{
    if (Scode.at(count) == '0')
    {
        insert(getInfo(), t);
        count++;
    }
    else
    {
        insert(getInfo(Scode.at(count + 1), 1), t);
        count += 2;
        size++;
        return;
    }
    mapToChildren(t->left);
    mapToChildren(t->right);
}

template <class Comparable>
bool BTree<Comparable>::atLeaf() const
{
    if (!currentNode->left && !currentNode->right)
        return true;
    return false;
}

template <class Comparable>
bool BTree<Comparable>::_getSymbol(std::string _c)
{
    c = char();
    symbolFound = false;
    if (!returnSymbol(root->left, _c))
        returnSymbol(root->right, _c);
    return symbolFound;
}

template <class Comparable>
bool BTree<Comparable>::returnSymbol(BinaryNode<Comparable> *t, std::string code)
{
    if (!t->left && !t->right)
    {
        if (t->element.code == code)
        {
            c = t->element.symbol;
            symbolFound = true;
            return true;
        }
        return false;
    }
    if (returnSymbol(t->left, code))
        return true;
    return returnSymbol(t->right, code);
}

template class BTree<Fileinfo<int>>;