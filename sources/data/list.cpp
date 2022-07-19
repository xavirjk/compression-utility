#include "list.h"

template <class Object>
List<Object>::List()
{
    header = new ListNode<Object>;
}

template <class Object>
bool List<Object>::isEmpty() const
{
    return header->next == nullptr;
}

template <class Object>
void List<Object>::ensureEmpty()
{
    header->next = nullptr;
    header->previous = nullptr;
}

template <class Object>

ListItr<Object> List<Object>::zeroth() const
{
    return ListItr<Object>(header);
}

template <class Object>
ListItr<Object> List<Object>::first() const
{
    return ListItr<Object>(header->next);
}
template <class Object>
ListItr<Object> List<Object>::findMin() const
{
    ListNode<Object> *itr = header->next;
    ListNode<Object> *min;
    if (itr->element.flagged())
        min = itr->next;
    else
        min = itr;
    while (itr != nullptr)
    {
        if (!itr->element.flagged() && itr->element.getFrequency() < min->element.getFrequency())
            min = itr;
        itr = itr->next;
    }
    min->element.flag();
    return ListItr<Object>(min);
}

template <class Object>
ListItr<Object> List<Object>::last() const
{
    if (isEmpty())
        return zeroth();

    ListItr<Object> itr = first();
    ListItr<Object> ls;
    for (; !itr.isPastEnd(); itr.advance())
        ls = itr;
    return ls;
}
template <class Object>
const int List<Object>::size() const
{
    int count = 0;
    if (isEmpty())
        return count;
    ListItr<Object> itr = first();
    for (; !itr.isPastEnd(); itr.advance())
        count++;
    return count;
}

template <class Object>
bool List<Object>::findSymbol(const char &ch) const
{
    ListNode<Object> *itr = header->next;
    while (itr != nullptr)
    {

        if (itr->element.findSymbol(ch))
            return true;
        itr = itr->next;
    }
    return false;
}

template <class Object>
void List<Object>::remove(const ListItr<Object> &p)
{
    ListItr<Object> pr = p.current->previous;
    if (pr.current->next != nullptr)
    {
        ListNode<Object> *oldNode = pr.current->next;
        pr.current->next = pr.current->next->next;
        pr.current->next->previous = pr.current;
        delete oldNode;
    }
}
template <class Object>
void List<Object>::clearProcedure(const ListItr<Object> &p)
{
    int sz = size();
    ListItr<Object> pr = p.current->previous;
    if (pr.current->next != nullptr)
    {
        ListNode<Object> *oldNode = pr.current->next;
        pr.current->next = pr.current->next->next;
        if (sz == 1)
            header->next = nullptr;
        else
            pr.current->next->previous = pr.current;
        delete oldNode;
    }
}

template <class Object>
void List<Object>::insert(Object &x, const ListItr<Object> &p)
{
    if (p.current != nullptr)
        p.current->next = new ListNode<Object>(x, p.current->next, p.current);
}

template <class Object>
void List<Object>::printList()
{
    if (isEmpty())
        std::cout << "Empty List " << std::endl;
    else
    {
        ListItr<Object> itr = first();
        for (; !itr.isPastEnd(); itr.advance())
            itr.retrieve().print();
    }
    std::cout << std::endl;
}

template <class Object>
void List<Object>::makeEmpty()
{
    while (!isEmpty())
        clearProcedure(first());
}

template <class Object>
List<Object>::~List() {}

template class List<BTree<Fileinfo<int>>>;