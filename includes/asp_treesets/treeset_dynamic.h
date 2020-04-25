#ifndef TREESET_DYNAMIC_H
#define TREESET_DYNAMIC_H

#include "includes/utils/utils.h"

#include <cassert>
#include <utility>
#include <tuple>

template <typename T>
class treeset_dynamic
{
    friend TestPlug<treeset_dynamic<T>>;
    struct node_t;
public:
    using elem_t = T;
public:
    void insert(T x)
    {
	node_t *node,*parent;
	std::tie(node,parent) = find(x,root,nullptr);
	if(node == nullptr)
	{
	    node_t* node_t::*side = ( parent != nullptr && x < parent->val)? &node_t::left : &node_t::right;
	    node_t* new_node = new node_t{nullptr,nullptr,x};
	    append_node( new_node, parent, side );
	}
    }
    bool contains(T x)
    {
	return find(x,root,nullptr).first != nullptr;
    }
    void remove(T x)
    {
	node_t *node,*parent;
	std::tie(node,parent) = find(x,root,nullptr);
	if( node != nullptr)
	{
	    if( node->left == nullptr )
		node = exclude_single_node(node,parent,&node_t::right);
	    else if( node->right == nullptr )
		node = exclude_single_node(node,parent,&node_t::left);
	    else
	    {
		bool rand = (((ptrdiff_t)node/sizeof(node_t*))%7) > 3;
		auto side = (rand)? &node_t::left : &node_t::right;
		node = exclude_double_node(node,parent,side);
	    }
	    delete node;
	}
    }
    ~treeset_dynamic()
    {
	if(root != nullptr)
	    del_subtree(root);
    }
private:
    static std::pair<node_t*,node_t*> find(T x,node_t* node,node_t* parent)
	{
	    while( node != nullptr && node->val != x )
		std::tie( parent, node ) = { node, (node->val < x)? node->right : node->left };
	    return { node, parent };
	}
    static std::pair<node_t*,node_t*> traverse_last(node_t* node, node_t* parent, node_t* node_t::*side )
    	{
    	    assert(node != nullptr);
    	    assert(side != nullptr);
    	    while( node->*side != nullptr )
    		std::tie( parent, node) = { node, node->*side };
    	    return { node, parent };
    	}
    static void del_subtree(node_t* node)
	{
	    assert( node != nullptr );
	    if( node->left != nullptr )
		del_subtree(node->left);
	    if( node->right != nullptr )
		del_subtree(node->right);
	    delete node;
	}
    void append_node(node_t* node,node_t* new_parent, node_t* node_t::*side)
    {
	assert(side != nullptr);
	if(new_parent != nullptr)
	    new_parent->*side = node;
	else
	    root = node;
    }
    node_t* exclude_single_node( node_t* node, node_t* parent, node_t* node_t::*side )
    {
	assert(node != nullptr);
	assert(side != nullptr);
	node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	append_node(node->*side, parent, parent_side);
	return node;
    }
    node_t* exclude_double_node( node_t* node, node_t* parent, node_t* node_t::*side )
    {
	assert(node != nullptr);
	assert(side != nullptr);
	node_t* node_t::*trav_side = ((side == &node_t::left)? &node_t::right : &node_t::left);
	node_t* trav_parent = node->*side;
	node_t* trav_node = trav_parent->*trav_side;
	if( trav_node != nullptr )
	    std::tie( trav_node, trav_parent ) = traverse_last( trav_node, trav_parent, trav_side);
	else
	    std::tie( trav_node, trav_parent ) = { node->*side, node };
	exclude_single_node( trav_node, trav_parent, side );
	node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	append_node(trav_node, parent, parent_side);
	append_node(node->left, trav_node, &node_t::left);
	append_node(node->right, trav_node, &node_t::right);
	return node;
    }
private:
    struct node_t
    {
	node_t *left,*right;
	T val;
    };
    node_t* root = nullptr;
};

#endif /*TREESET_DYNAMIC_H*/
