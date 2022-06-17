#include "binarynode.h"
#include "fileinfo.h"
#include <iostream>
using namespace std;
template <class Comparable>
class BinarySearchTree
{
public:
    explicit BinarySearchTree(const Comparable &notFound);
    BinarySearchTree(const BinarySearchTree &rhs);
    ~BinarySearchTree();

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    const Comparable &find(const Fileinfo<int> &f) const;
    bool findSymbol(char ch) const;
    bool isEmpty() const;
    void printTree() const;

    void makeEmpty();
    void insert(const Fileinfo<int> &f);
    void insertLeft(const BinarySearchTree *rhs);
    void insertRight(const BinarySearchTree *rhs);
    void remove(const Fileinfo<int> &f);
    int getFrequency(const BinarySearchTree *rhs) const;

    const BinarySearchTree &operator=(const BinarySearchTree &rhs);

private:
    BinaryNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND = -1;

    const Comparable &elementAt(BinaryNode<Comparable> *t) const;
    void insert(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    void insertLeft(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    void insertRight(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    void remove(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    BinaryNode<Comparable> *findMin(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *findMax(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *find(const Fileinfo<int> &f, BinaryNode<Comparable> *t) const;
    void makeEmpty(BinaryNode<Comparable> *&t) const;
    void preOrder(BinaryNode<Comparable> *t) const;
    BinaryNode<Comparable> *clone(BinaryNode<Comparable> *t) const;
    bool hasSymbol(BinaryNode<Comparable> *t, char ch) const;
};