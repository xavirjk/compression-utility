#ifndef LIST_H_
#define LIST_H_

#include "listitr.h"
#include "btree.h"
#include "huffman.h"

template <class Object>
class List
{
public:
    List();
    List(const List &rhs);
    ~List();
    bool isEmpty() const;
    ListItr<Object> zeroth() const;
    ListItr<Object> first() const;
    ListItr<Object> last() const;
    const int size() const;
    void inset(Object &x, const ListItr<Object> &p);

    ListItr<Object> findMin() const;
    bool findSymbol(const char &ch) const;
    void remove(const ListItr<Object> &p);
    void printList();
    void makeEmpty();

    const List &operator=(const List &rhs);

private:
    ListNode<Object> *header;
};
#endif //LIST_H_