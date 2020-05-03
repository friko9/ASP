#ifndef LIST_ARRAY_ENCHANCED_H
#define LIST_ARRAY_ENCHANCED_H

#include "./impl/list_array_enchanced_impl.h"
#include "../utils/utils.h"

#include <cassert>
#include <vector>

template <typename T>
class list_array_enchanced
{  
  using index_t = typename std::vector<T>::size_type;
  using BidirectionalOrder = impl::list_array_enchanced::BidirectionalOrder<index_t>;
public:
  using elem_t = T;
public:    
  void insert(elem_t value_arg)
  {
    elems.push_back(value_arg);
    order.push_back();
  }
  bool contains(elem_t value_arg)
  {
    return find(value_arg) != tail;
  }
  void remove(elem_t value_arg)
  {
    index_t node = find(value_arg);
    if( node == tail ) return;

    order.remove_node(node);
    elems[node] = std::move(elems.back());
    elems.pop_back();
  }
private:
  index_t size() const  { return elems.size(); }
  index_t find(elem_t value_arg)
  {
    index_t node = order.get_next(head);
    while( node != tail && elems[node] != value_arg )
      node = order.get_next(node);
    return node;
  }
private:
  static constexpr index_t head = BidirectionalOrder::get_head();
  static constexpr index_t tail = BidirectionalOrder::get_tail();
  std::vector<T> elems = { elem_t{}, elem_t{} };
  BidirectionalOrder order;
};

#endif /*LIST_ARRAY_ENCHANCED_H*/
