#ifndef TREESET_DYNAMIC_H
#define TREESET_DYNAMIC_H

#include "includes/utils/utils.h"

#include <utility>

template <typename T>
class treeset_dynamic
{
    friend TestPlug<treeset_dynamic<T>>;
    struct node_t
    {
	T val;
	node_t *left,*right;
    };
    node_t* root = nullptr;
    static std::pair<node_t*,node_t*> find(T x,node_t* node,node_t* parent)
	{
	    if( node == nullptr || x == node->val )
		return std::make_pair(node,parent);
	    parent = node;
	    node = ( node->val < x )? node->right : node->left;
	    return find(x,node,parent);
	}
    node_t* exclude_single_node( node_t* node, node_t* parent, node_t* node_t::*side )
	{
	    if( parent == nullptr )
		root = node->*side;
	    else if( parent->left == node )
		parent->left = node->*side;
	    else
		parent->right = node->*side;
	    return node;
	}
    node_t* exclude_double_node( node_t* node, node_t* parent, node_t* node_t::*branch_side )
	{
	    node_t* node_t::*trav_side = ((branch_side == &node_t::left)? &node_t::right : &node_t::left);
	    node_t* trav_parent = node->*branch_side;
	    node_t* trav_node = trav_parent->*trav_side;
	    if( trav_node == nullptr )
	    {
		trav_node = node->*branch_side;
		trav_parent = node;
	    } else
	    {
		for(; trav_node->*trav_side != nullptr; trav_node = trav_node->*trav_side)
		    trav_parent = trav_node;
	    }
	    std::swap( trav_node->val, node->val );
	    return exclude_single_node( trav_node, trav_parent, branch_side );
	}
    void del_subtree(node_t* root)
	{
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
public:
    void insert(T x)
	{
	    node_t *node,*parent;
	    std::tie(node,parent) = find(x,root,nullptr);
	    if(node != nullptr)
		return;
	    node_t* new_node = new node_t{x,nullptr,nullptr};
	    node_t** link = &root;
	    if(parent != nullptr )
		link = (parent->val < x)? &(parent->right) : &(parent->left);
	    *link =  new_node;
	}
    bool contains(T x)
	{
	    return find(x,root,nullptr).first != nullptr;
	}
    void remove(T x)
	{
	    node_t *node,*parent;
	    std::tie(node,parent) = find(x,root,nullptr);
	    if( node == nullptr) return;
	    
	    if( node->left == nullptr ) // also works for leafs
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
    ~treeset_dynamic()
	{
	    del_subtree(root);
	}
};

#endif /*TREESET_DYNAMIC_H*/
