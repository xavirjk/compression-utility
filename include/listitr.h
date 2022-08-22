#ifndef LISTITR_H_
#define LISTITR_H_

#include "listnode.h"
template <class Object>
class ListItr
{
public:
    ListItr() : current(nullptr) {}
    ~ListItr() {}
    bool isPastEnd() const
    {
        return current == nullptr;
    }
    void advance()
    {
        if (!isPastEnd())
            current = current->next;
    }
    Object &retrieve() const
    {
        if (isPastEnd())
            throw -1;
        return current->element;
    }

private:
    ListNode<Object> *current;
    ListItr(ListNode<Object> *theNode) : current(theNode){};
    friend class List<Object>;
};

#endif //LISTITR_H_