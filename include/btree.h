#ifndef BTree_H_
#define BTree_H_

#include "binarynode.h"
#include "utils.h"
#include "huffman.h"
template <class Comparable>
class BTree
{
public:
    explicit BTree();
    BTree(const BTree &rhs);
    ~BTree();

    bool findSymbol(char ch) const;
    bool isEmpty() const;
    void print() const;
    char _symbol() const;

    Huffman *huffman(const int size = 0);

    void insert(const Fileinfo<int> &f);
    int depth();
    void insertLeft(const BTree &rhs);
    void insertRight(const BTree &rhs);
    int getFrequency() const;
    void flag();

    bool flagged() const;
    std::string getTree();
    void mapTree(std::string tree);
    bool _getSymbol(std::string _code);
    int len() const;
    bool atLeaf() const;
    void _rcurrentNode();

    const BTree &operator=(const BTree &rhs);
    BinaryNode<Comparable> *currentNode;

private:
    BinaryNode<Comparable> *root;
    int count = 0, size = 0;
    std::string Scode = "";
    char c;
    Huffman *hf;
    bool symbolFound;

    void insert(const Fileinfo<int> &f, BinaryNode<Comparable> *&t) const;
    void preOrder(BinaryNode<Comparable> *t) const;
    void depth(BinaryNode<Comparable> *t);
    BinaryNode<Comparable> *clone(BinaryNode<Comparable> *t) const;
    void recordWeights(BinaryNode<Comparable> *t);
    void popBack();
    void _switch();
    void appendToTree(BinaryNode<Comparable> *t);
    void mapToChildren(BinaryNode<Comparable> *&t);
    bool returnSymbol(BinaryNode<Comparable> *t, std::string code);
};

#endif //BTree_H_
