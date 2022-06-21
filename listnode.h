template <class Object>
class List; //Incomplete declaration;

template <class Object>
class ListItr; //Incomplete declaration;

template <class Object>
class ListNode
{
public:
    ListNode(Object *theElement = nullptr, ListNode *n = nullptr, ListNode *p = nullptr) : element(theElement), next(n), previous(p){};
    ~ListNode(){};

    Object *element;
    ListNode *next;
    ListNode *previous;
    friend class List<Object>;
    friend class ListItr<Object>;
};