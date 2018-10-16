#ifndef LIST_DYNAMIC_H
#define LIST_DYNAMIC_H

#include "includes/utils/utils.h"

template <typename T>
class list_dynamic
{
    struct node_t{
	T val;
	node_t* next;
    };
    friend TestPlug<list_dynamic<T>>;
    node_t head {0,nullptr};
    std::pair<node_t*,node_t*> find( T x )
	{
	    node_t* prev = &head;
	    node_t* node = head.next;
	    while(node != nullptr && node->val != x)
		std::tie(prev,node) = { node, node->next };
	    return { prev, node };
	}
public:
    void insert(const T x)
	{
	    node_t* node = new node_t {x,head.next};
	    head.next = node;
	}
    bool contains(T x)
	{
	    return find(x).second != nullptr;
	}
    void remove(T x)
	{
	    node_t *prev,*node;
	    std::tie(prev,node) = find(x);
	    if(node != nullptr)
	    {
		prev->next = node->next;
		delete node;
	    }
	}
};

#endif /*LIST_DYNAMIC_H*/
