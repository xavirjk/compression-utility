#ifndef LISTNODE_H_
#define LISTNODE_H_

template <class Object>
class List; //Incomplete declaration;

template <class Object>
class ListItr; //Incomplete declaration;

template <class Object>
class ListNode
{
public:
    ListNode(){};
    ListNode(Object &theElement, ListNode *n = nullptr, ListNode *p = nullptr) : next(n), previous(p)
    {
        element = theElement;
    };
    ~ListNode(){};

    Object element;
    ListNode *next;
    ListNode *previous;
    friend class List<Object>;
    friend class ListItr<Object>;
};

#endif //LISTNODE