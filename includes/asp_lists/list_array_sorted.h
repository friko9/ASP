#ifndef LIST_ARRAY_SORTED_H
#define LIST_ARRAY_SORTED_H

#include "impl/list_array_sorted_impl.h"

#include <cassert>
#include <vector>

template <typename T>
class list_array_sorted
{
  using index_t = typename std::vector<T>::size_type;
  using BidirectionalOrder = impl::list_array_sorted::BidirectionalOrder<index_t>;
  using elem_t = T;
public:
  static constexpr index_t null = BidirectionalOrder::null;
public:
  void insert(T x)
  {
    m_elems.push_back(x);
    m_order.insert(find(x));
  }
  bool contains(T x)
  {
    index_t pos = find(x);
    return pos != null && m_elems[pos] == x;
  }
  void remove(T x)
  {
    index_t n = find(x);
    if( n == null || m_elems[n] != x ) return;
    m_order.remove_node(n);
    m_elems[n] = std::move(m_elems.back());
    m_elems.pop_back();
  }
private:
  index_t size()
  { return m_elems.size(); }
  index_t find(T x)
  {
    index_t node = m_order.get_head();
    while( node != null && m_elems[node] < x )
      node=m_order.get_next(node);
    return node;
  }
private:
  std::vector<T> m_elems;
  BidirectionalOrder m_order;
};

#endif /*LIST_ARRAY_SORTED_H*/
