#ifndef LIST_DYNAMIC_H
#define LIST_DYNAMIC_H

#include "includes/utils/utils.h"
#include "list_common.h"

template <typename T>
class list_dynamic
{
    friend TestPlug<list_dynamic<T>>;
    node<T> head {0,nullptr};
public:
    void insert(const T x)
	{
	    node<T>* n = new node<T> {x,head.next};
	    head.next = n;
	}
    bool contains(T x)
	{
	    node<T>* n = head.next;
	    while(n!=nullptr && n->val != x)
		n=n->next;
	    return n != nullptr;
	}
    void remove(T x)
	{
	    node<T>* prev = &head;
	    node<T>* n = head.next;
	    while(n!=nullptr && n->val != x)
	    {
		prev=n;
		n=n->next;
	    }
	    if(n==nullptr) return;
	    prev->next = n->next;
	    delete n;
	}
};

#endif /*LIST_DYNAMIC_H*/
