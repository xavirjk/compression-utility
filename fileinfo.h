#ifndef FILEINFO_H_
#define FILEINFO_H_

template <class Comparable>
class BinarySearchTree;

template <class Object>
class Fileinfo
{
public:
    Fileinfo();
    Fileinfo(const char &s, Object &f) : symbol(s), frequency(f){};
    ~Fileinfo(){};
    friend class BinarySearchTree<Object>;

    const Fileinfo &operator=(const Fileinfo &rhs)
    {
        if (this != &rhs)
        {
            /*makeEmpty();
            root = clone(rhs.root);*/
        }
        return *this;
    }
    Object frequency;
    const char symbol;
    bool flag = false;
};
#endif //FILEINFO_H_