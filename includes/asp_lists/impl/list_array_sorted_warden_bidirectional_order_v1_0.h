#ifndef LIST_ARRAY_SORTED_WARDEN_BIDIRECTIONAL_ORDER_V1_0_H
#define LIST_ARRAY_SORTED_WARDEN_BIDIRECTIONAL_ORDER_V1_0_H

#include <cassert>
#include <vector>
#include <limits>

namespace impl
{
  namespace list_array_sorted_warden
  {
    namespace v1_0
    {
      template <typename T>
      struct BidirectionalOrder
      {
	using index_t = T;
	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
	static constexpr index_t m_head {1};
	static constexpr index_t m_tail {0};
      public:
	static constexpr index_t null = std::numeric_limits<index_t>::max();
      public:
	index_t get_head()
	{
	  return m_head;
	}
	index_t get_tail()
	{
	  return m_tail;
	}
	void insert(index_t pos)
	{
	  index_t node = m_next.size();
	  index_t node_prev = m_prev[pos];
	  m_next.push_back(pos);
	  m_prev.push_back(node_prev);

	  m_next[node_prev] = node;
	  m_prev[pos] = node;
	}
	index_t get_next(index_t node)
	{
	  assert(node < m_next.size());
	  return m_next[node];
	}
	void remove_node(index_t node)
	{
	  assert( node < m_next.size());
	  assert( node != m_head );
	  assert( node != m_tail );

	  index_t& node_prev_next = m_next[m_prev[node]];
	  index_t& node_next_prev = m_prev[m_next[node]];
	  node_next_prev = m_prev[node];
	  node_prev_next = m_next[node];

	  move_last_to(node);
	  m_next.pop_back();
	  m_prev.pop_back();
	}
	void move_last_to(index_t node)
	{
	  assert( node < m_next.size());
	  assert( node != m_head );
	  assert( node != m_tail );
	  if(node == m_next.size()-1) return;

	  index_t& prev_node_next = m_next[m_prev.back()];
	  index_t& next_node_prev = m_prev[m_next.back()];
	  prev_node_next = node;
	  next_node_prev = node;

	  m_next[node] = m_next.back();
	  m_prev[node] = m_prev.back();
	}
      private:
	std::vector<index_t> m_next = { m_head, m_tail };
	std::vector<index_t> m_prev = { m_head, m_tail };
      };
    }
  }
}

#endif /* LIST_ARRAY_SORTED_WARDEN_BIDIRECTIONAL_ORDER_V1_0_H */
