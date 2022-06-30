#ifndef BINARYNODE_H_
#define BINARYNODE_H_

template <class Comparable>
class BTree;

template <class Comparable>
class BinaryNode
{
public:
    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt) : element(theElement), left(lt), right(rt){};
    ~BinaryNode(){};

    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    friend class BTree<Comparable>;
};
#endif //BINARYNODE_H_