#include "listitr.h"
#include "binarysearchtree.h"
#include <iostream>
using namespace std;
#include <string>
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
    void insert(Object *x, const ListItr<Object> &p);
    ListItr<Object> find(Object *x) const;
    ListItr<Object> findPrevious(Object *x) const;
    bool findSymbol(const char &ch) const;
    void remove(Object *x);
    void printList(const List<Object> &theList);
    void makeEmpty();

    const List &operator=(const List &rhs);

private:
    ListNode<Object> *header;
};