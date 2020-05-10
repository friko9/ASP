#ifndef LIST_ARRAY_SORTED_WARDEN_H
#define LIST_ARRAY_SORTED_WARDEN_H

#include "impl/list_array_sorted_warden_impl.h"

#include <cassert>
#include <limits>
#include <vector>

template <typename T>
class list_array_sorted_warden
{
  using index_t = typename std::vector<T>::size_type;
  using BidirectionalOrder = impl::list_array_sorted_warden::BidirectionalOrder<index_t>;
public:
  using elem_t = T;
public:
  list_array_sorted_warden()
  {
    constexpr T max  = std::numeric_limits<T>::max();
    constexpr T min  = std::numeric_limits<T>::min();
    m_elems.push_back(T{max});
    m_elems.push_back(T{min});
  }
  void insert(T x)
  {
    m_elems.push_back(x);
    m_order.insert(find(x));
  }
  bool contains(T arg)
  {
    index_t node = find(arg);
    return (node == m_order.get_tail() )? false : (m_elems[node] == arg);
  }
  void remove(T x)
  {
    index_t n = find(x);
    if( n == m_order.get_tail() || m_elems[n] != x ) return;
    m_order.remove_node(n);
    m_elems[n] = std::move(m_elems.back());
    m_elems.pop_back();
  }
private:
  index_t size()
  {
    return m_elems.size();
  }
  index_t find(T x)
  {
    index_t node = m_order.get_next(m_order.get_head());
    while( m_elems[node] < x )
      node=m_order.get_next(node);
    return node;
  }
private:
  std::vector<T> m_elems;
  BidirectionalOrder m_order;
};
#endif /*LIST_ARRAY_SORTED_WARDEN_H*/
