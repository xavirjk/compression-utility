template <class Object>
class List; //Incomplete declaration;

template <class Object>
class ListItr; //Incomplete declaration;

template <class Object>
class ListNode
{
public:
    ListNode(Object *theElement = nullptr, ListNode *n = nullptr) : element(theElement), next(n){};
    ~ListNode(){};

    Object *element;
    ListNode *next;
    friend class List<Object>;
    friend class ListItr<Object>;
};