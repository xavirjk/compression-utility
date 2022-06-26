#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include "binarynode.h"
#include "fileinfo.h"
#include "huffman.h"
#include <iostream>
using namespace std;
template <class Comparable>
class BinarySearchTree : public Entity
{
public:
    explicit BinarySearchTree(const Comparable &notFound);
    BinarySearchTree(const BinarySearchTree &rhs);
    ~BinarySearchTree();

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    const Comparable &find(const Fileinfo<int> &f) const;
    bool findSymbol(char ch) const override;
    bool isEmpty() const;
    void print() const override;
    Huffman *huffman(const int &size);

    void makeEmpty();
    void insert(const Fileinfo<int> &f);
    int depth();
    void insertLeft(const BinarySearchTree *rhs);
    void insertRight(const BinarySearchTree *rhs);
    void remove(const Fileinfo<int> &f);
    int getFrequency() const override;
    void flag() override;
    bool flagged() const override;
    string getTree();

    const BinarySearchTree &operator=(const BinarySearchTree &rhs);

private:
    BinaryNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND = -1;
    int count = 0;
    string Scode = "";
    Huffman *hf;

    const Comparable &
    elementAt(BinaryNode<Comparable> *t) const;
    void insert(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    void remove(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    BinaryNode<Comparable> *findMin(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *findMax(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *find(const Fileinfo<int> &f, BinaryNode<Comparable> *t) const;
    void makeEmpty(BinaryNode<Comparable> *&t) const;
    void preOrder(BinaryNode<Comparable> *t) const;
    void depth(BinaryNode<Comparable> *t);
    BinaryNode<Comparable> *clone(BinaryNode<Comparable> *t) const;
    bool hasSymbol(BinaryNode<Comparable> *t, char ch) const;
    void recordWeights(BinaryNode<Comparable> *t);
    void popBack();
    void _switch();
    void appendToTree(BinaryNode<Comparable> *t);
};

#endif //BINARYSEARCHTREE_H_