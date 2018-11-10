#ifndef LIST_DYNAMIC_H
#define LIST_DYNAMIC_H

#include "includes/utils/utils.h"

template <typename T>
class list_dynamic
{
public:
    using elem_t = T;
    struct node_t{
	T val;
	node_t* next;
    };
private:
    friend TestPlug<list_dynamic<T>>;
private:
    node_t head {0,nullptr};
private:
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
    ~list_dynamic()
	{
	    node_t* prev = &head;
	    node_t* node = head.next;
	    while(node != nullptr)
	    {
		std::tie(prev,node) = { node, node->next };
		delete prev;
	    }
	    delete node;
	}
    
};

#endif /*LIST_DYNAMIC_H*/
