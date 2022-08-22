#ifndef FILEINFO_H_
#define FILEINFO_H_
#include <string>

template <class Comparable>
class BTree;

template <class Object>
class Fileinfo
{
public:
    Fileinfo();
    Fileinfo(const char &s, Object &f) : symbol(s), frequency(f){};
    ~Fileinfo(){};
    friend class BTree<Object>;

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
    std::string code;
    bool flag = false;
};
#endif //FILEINFO_H_