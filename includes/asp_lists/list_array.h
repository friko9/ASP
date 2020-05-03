#ifndef LIST_ARRAY_H
#define LIST_ARRAY_H

#include "./impl/list_array_impl.h"
#include "includes/utils/utils.h"

#include <cassert>
#include <limits>
#include <vector>
#include <typeinfo>

template <typename T>
class list_array
{
  using index_t = typename std::vector<T>::size_type;
public:
  using elem_t = T;
public:
  void insert(elem_t arg)
  {
    order_.push_new_head();
    elems_.push_back(arg);
  }
  bool contains(elem_t x)
  {
    return find(x) != null_;
  }
  void remove(elem_t x)
  {
    auto node = find(x);
    if(node == null_) return;
    auto last = size()-1;
    exclude_elem(node);
    move_elem(last,node);
    elems_.pop_back();
    order_.pop_back();
  }
private:
  index_t size()
  { return elems_.size(); }
  void move_elem(index_t src,index_t dst)
  {
    order_.move_elem(src,dst);
    elems_[dst] = std::move(elems_[src]);
  }
  void exclude_elem(index_t node) { order_.exclude_elem(node); }
  index_t find(elem_t x)
  {
    auto node = order_.get_head();
    while( node != null_ && elems_[node] != x )
      node = order_.get_next(node);
    return node;
  }
private:
  static constexpr index_t null_ = impl::list_array::BidirectionalOrder<index_t>::null_;
  impl::list_array::BidirectionalOrder<index_t> order_;
  std::vector<elem_t> elems_;
};

#endif /*LIST_ARRAY_H*/
