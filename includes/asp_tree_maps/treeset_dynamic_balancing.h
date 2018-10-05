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
	node_t *left,*right,*up;
	T val;
	int_fast8_t height;
    };
    node_t* root = nullptr;
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
    void del_subtree(node_t* root) const
	{
	    if( root == nullptr ) return;
	    if( root->left != nullptr )
	    {
		del_subtree(root->left);
		delete root->left;
	    }
	    if( root->right != nullptr )
	    {
		del_subtree(root->right);
		delete root->right;
	    }
	}
    std::pair<const node_t*,const node_t*> find(T x, const node_t* node) const
	{
	    const node_t* parent = nullptr;
	    while( node != nullptr && node->val != x )
	    {
		parent = node;
		node = ( node->val < x )? node->right : node->left;
	    }
	    return std::make_pair(node,parent);
	}
    std::pair<node_t*,node_t*> exclude_single_node( node_t* node, node_t* node_t::*node_side )
	{
	    assert(node != nullptr);
	    assert(node_side != nullptr);
	    node_t* parent = node->up;
	    node_t* node_t::*parent_side = (parent != nullptr && parent->left == node)? &node_t::left : &node_t::right;
	    append_node(node->*node_side, parent, parent_side);
	    return std::make_pair(node,parent);
	}
    const node_t* traverse_last(const node_t* node, node_t* node_t::*side ) const
	{
	    assert(node != nullptr);
	    assert(side != nullptr);
	    while( node->*side != nullptr )
		node = node->*side;
	    return node;
	}
    std::pair<node_t*,node_t*> exclude_double_node( node_t* node, node_t* node_t::*branch_side )
	{
	    assert(node != nullptr);
	    assert(branch_side != nullptr);
	    node_t* node_t::*trav_side = ((branch_side == &node_t::left)? &node_t::right : &node_t::left);
	    node_t* trav_parent = node->*branch_side;
	    node_t* trav_node = const_cast<node_t*>(traverse_last(trav_parent,trav_side));
	    exclude_single_node( trav_node, branch_side );
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
		int_fast8_t hl = (node->left == nullptr)? 0 : node->left->height;
		int_fast8_t hr = (node->right == nullptr)? 0 : node->right->height;
		int_fast8_t balance = hl-hr;
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
	    if (root != nullptr)
	    {		
		const node_t *node,*parent;
		std::tie(node,parent)= find(x,root);
		if( node != nullptr) return;
		node_t* new_node = new node_t{nullptr,nullptr,nullptr,x,0};
		node_t* node_t::*append_side = (x < parent->val)? &node_t::left : &node_t::right;
		append_node(new_node,const_cast<node_t*>(parent),append_side);
		rebalance(new_node);
	    }else
		root = new node_t{nullptr,nullptr,nullptr,x,0};
	}
    bool contains(T x)
	{
	    return find(x,root).first != nullptr;
	}
    void remove(T x)
	{
	    node_t *node,*rebalance_parent;
	    node = const_cast<node_t*>(find(x,root).first);
	    if( node == nullptr) return;

	    if( node->left == nullptr ) // also works for leafs
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
    ~treeset_dynamic_balancing()
	{
	    del_subtree(root);
	}
};

#endif /*TREESET_DYNAMIC_BALANCING_H*/

