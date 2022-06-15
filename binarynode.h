template <class Comparable>
class BinarySearchTree;

template <class Comparable>
class BinaryNode
{
public:
    BinaryNode(const Comparable &theElement, BinaryNode *lt, BinaryNode *rt) : element(theElement), left(lt), right(rt){};
    ~BinaryNode(){};

    Comparable element;
    BinaryNode *left;
    BinaryNode *right;

    friend class BinarySearchTree<Comparable>;
};