#ifndef BTree_H_
#define BTree_H_

#include "binarynode.h"
#include "utils.h"
//#include "fileinfo.h"
#include "huffman.h"
#include <iostream>
using namespace std;
template <class Comparable>
class BTree : public Entity
{
public:
    explicit BTree(const Comparable &notFound);
    BTree(const BTree &rhs);
    ~BTree();

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    const Comparable &find(const Fileinfo<int> &f) const;
    bool findSymbol(char ch) const override;
    bool isEmpty() const;
    void print() const override;
    string getCode(char ch);
    char _symbol() const;
    Huffman *huffman(const int size = 0, bool canonize = true);

    void makeEmpty();
    void insert(const Fileinfo<int> &f);
    int depth();
    void insertLeft(const BTree *rhs);
    void insertRight(const BTree *rhs);
    void remove(const Fileinfo<int> &f);
    int getFrequency() const override;
    void flag() override;
    bool flagged() const override;
    string getTree();
    void mapTree(string tree);
    void canonized(string path, char c);
    void createRoot();
    bool _getSymbol(string _code);
    int len() const;
    bool atLeaf() const;
    void _rcurrentNode();

    const BTree &operator=(const BTree &rhs);
    BinaryNode<Comparable> *currentNode;

private:
    BinaryNode<Comparable> *root;
    const Comparable ITEM_NOT_FOUND = -1;
    int count = 0, size = 0;
    string Scode = "";
    char c;
    Huffman *hf;
    bool symbolFound, canonical_flag = true;

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
    void mapToChildren(BinaryNode<Comparable> *&t);
    bool returnCode(BinaryNode<Comparable> *t, char ch);
    bool returnSymbol(BinaryNode<Comparable> *t, string code);
    void canonizeChildren(BinaryNode<Comparable> *&t, string code, char _c, int index = 1);
};

#endif //BTree_H_