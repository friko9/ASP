#ifndef TREESET_DYNAMIC_BALANCING_H
#define TREESET_DYNAMIC_BALANCING_H

#include "includes/utils/utils.h"

#include <cassert>
#include <cstdint>

template <typename T>
class treeset_dynamic_balancing
{
    friend TestPlug<treeset_dynamic_balancing<T>>;
    struct node_t
    {
	using height_t = int_fast8_t;
	node_t *left,*right,*up;
	T val;
	height_t height;
    };
    using height_t = typename node_t::height_t;
private:
    node_t* root = nullptr;
private:
    static std::pair<node_t*,node_t*> find(T x, node_t* node)
	{
	    node_t* parent = nullptr;
	    while( node != nullptr && node->val != x )
		std::tie(parent, node) = { node, (node->val < x)? node->right : node->left };
	    return { node, parent };
	}
    static node_t* traverse_last(node_t* node, node_t* node_t::*side )
	{
	    assert(node != nullptr);
	    assert(side != nullptr);
	    while( node->*side != nullptr )
		node = node->*side;
	    return node;
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
private:
    void append_node(node_t* node,node_t* new_parent, node_t* node_t::*side)
	{
	    auto other_side = (side == &node_t::left)? &node_t::right : &node_t::left;
	    if( new_parent != nullptr)
	    {
		int h1 = (new_parent->*other_side == nullptr)? 0 : (new_parent->*other_side)->height;
		int h2 = (node == nullptr)? 0 : node->height;
		new_parent->height = std::max(h1,h2) + 1;
		new_parent->*side = node;
	    }else
		root = node;
	    if(node != nullptr)
		node->up = new_parent;
	}
    std::pair<node_t*,node_t*> exclude_single_node( node_t* node, node_t* node_t::*side )
	{
	    assert(node != nullptr);
	    assert(side != nullptr);
	    node_t* parent = node->up;
	    node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	    append_node(node->*side, parent, parent_side);
	    return { node, parent };
	}
    std::pair<node_t*,node_t*> exclude_double_node( node_t* node, node_t* node_t::*side )
	{
	    assert(node != nullptr);
	    assert(side != nullptr);
	    node_t* node_t::*trav_side = ((side == &node_t::left)? &node_t::right : &node_t::left);
	    node_t* trav_parent = node->*side;
	    node_t* trav_node = traverse_last(trav_parent,trav_side);
	    exclude_single_node( trav_node, side );
	    node_t* parent = node->up;
	    node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	    append_node(trav_node, parent,parent_side);
	    append_node(node->left, trav_node, &node_t::left);
	    append_node(node->right, trav_node, &node_t::right);
	    return std::make_pair( node, trav_parent);
	}
    node_t* rebalance_case_1(node_t* origin, node_t* node)
	{
	    assert(origin != nullptr);
	    assert(node != nullptr);
	    node_t* parent = node->up;
	    node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	    node_t* node_t::*node_side = (node->left == origin)? &node_t::left : &node_t::right;
	    node_t* node_t::*origin_side = (node->left == origin)? &node_t::right : &node_t::left;
	    
	    append_node(origin, parent, parent_side);
	    append_node(origin->*origin_side, node, node_side);
	    append_node(node, origin, origin_side);
	    return origin;
	}
    node_t* rebalance_case_2(node_t* origin, node_t* node)
	{
	    assert(origin != nullptr);
	    assert(node != nullptr);
	    node_t* parent = node->up;
	    node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	    node_t* node_t::*node_side = (node->left == origin)? &node_t::left : &node_t::right;
	    node_t* node_t::*origin_side = (node->left == origin)? &node_t::right : &node_t::left;
	    node_t* new_top = origin->*origin_side;
	    
	    append_node(new_top,parent,parent_side);
	    append_node(new_top->*origin_side, node, node_side);
	    append_node(new_top->*node_side, origin, origin_side);
	    append_node(node,new_top,origin_side);
	    append_node(origin,new_top,node_side);
	    return new_top;
	}
    void rebalance(node_t* node)
	{
	    for(;node != nullptr; node = node->up)
	    {
		height_t hl = (node->left == nullptr)? 0 : node->left->height;
		height_t hr = (node->right == nullptr)? 0 : node->right->height;
		height_t balance = hl - hr;
		if( balance*balance < 4 )
		    node->height = std::max(hl,hr) + 1;
		else
		{
		    auto side = (hl < hr)? &node_t::right : &node_t::left;
		    auto oside = (hl < hr)? &node_t::left : &node_t::right;
		    auto origin = node->*side;
		    int r_h1 = (origin->*oside == nullptr)? 0 : (origin->*oside)->height;
		    int r_h2 = (origin->*side == nullptr)? 0 : (origin->*side)->height;
		    if( r_h1 > r_h2 )
			node = rebalance_case_2(origin, node);
		    else
			node = rebalance_case_1(origin, node);
		}
	    }
	}
public:
    void insert(T x)
	{
	    node_t *node,*parent;
	    std::tie(node,parent)= find(x,root);
	    if( node == nullptr)
	    {
		node_t* node_t::*side = (parent != nullptr && x < parent->val)? &node_t::left : &node_t::right;
		node_t* new_node = new node_t{nullptr,nullptr,nullptr,x,0};
		append_node(new_node, parent, side);
		rebalance(new_node);
	    }
	}
    bool contains(T x)
	{
	    return find(x,root).first != nullptr;
	}
    void remove(T x)
	{
	    node_t *node,*rebalance_parent;
	    node = find(x,root).first;
	    if( node != nullptr)
	    {
		if( node->left == nullptr )
		    std::tie(node,rebalance_parent) = exclude_single_node(node,&node_t::right);
		else if( node->right == nullptr )
		    std::tie(node,rebalance_parent) = exclude_single_node(node,&node_t::left);
		else
		{
		    int hl = (node->left == nullptr)? 0 : node->left->height;
		    int hr = (node->right == nullptr)? 0 : node->right->height;
		    auto side = ( hl < hr )? &node_t::left : &node_t::right;
		    std::tie(node,rebalance_parent) = exclude_double_node(node,side);
		}
		delete node;
		rebalance(rebalance_parent);
	    }
	}
    ~treeset_dynamic_balancing()
	{
	    if( root != nullptr)
		del_subtree(root);
	}
};

#endif /*TREESET_DYNAMIC_BALANCING_H*/

