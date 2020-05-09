#ifndef LIST_ARRAY_SORTED_BIDIRECTIONAL_ORDER_V1_0_H
#define LIST_ARRAY_SORTED_BIDIRECTIONAL_ORDER_V1_0_H

#include <cassert>
#include <vector>
#include <limits>

namespace impl
{
  namespace list_array_sorted
  {
    namespace v1_0
    {
      template <typename T>
      struct BidirectionalOrder
      {
	using index_t = T;
	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
      public:
	static constexpr index_t null = std::numeric_limits<index_t>::max();
      public:
	index_t get_head() { return m_head; }
	index_t get_tail() { return m_tail; }
	void insert(index_t pos)
	{
	  index_t last = m_next.size();
	  index_t n_prev = (pos != null)? m_prev[pos] : m_tail;

	  m_next.push_back(pos);
	  m_prev.push_back(n_prev);

	  if(n_prev != null)
	    m_next[n_prev] = last;
	  else
	    m_head = last;
	  if(pos != null)
	    m_prev[pos] = last;
	  else
	    m_tail = last;
	}
	index_t get_next(index_t node)
	{
	  assert(node < m_next.size());
	  return m_next[node];
	}
	void remove_node(index_t node)
	{
	  assert( node < m_next.size());

	  index_t& prev_node_next = (m_prev[node] != null)? m_next[m_prev[node]] : m_head;
	  index_t& next_node_prev = (m_next[node] != null)? m_prev[m_next[node]] : m_tail;
	  next_node_prev = m_prev[node];
	  prev_node_next = m_next[node];

	  move_last_to(node);
	  m_next.pop_back();
	  m_prev.pop_back();
	}
	void move_last_to(index_t node)
	{
	  assert( node < m_next.size());

	  if(node == m_next.size()-1) return;

	  index_t& prev_node_next = (m_prev.back() != null)? m_next[m_prev.back()] : m_head;
	  index_t& next_node_prev = (m_next.back() != null)? m_prev[m_next.back()] : m_tail;
	 
	  prev_node_next = node;
	  next_node_prev = node;
	  m_prev[node] = m_prev.back();
	  m_next[node] = m_next.back();
	}
      private:
	index_t m_head = null;
	index_t m_tail = null;
	std::vector<index_t> m_next;
	std::vector<index_t> m_prev;
      };
    }
  }
}

#endif /* LIST_ARRAY_SORTED_BIDIRECTIONAL_ORDER_V1_0_H */
