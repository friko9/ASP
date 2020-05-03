#ifndef LIST_ARRAY_ENCHANCED_BIDIRECTIONAL_ORDER_V1_0_H
#define LIST_ARRAY_ENCHANCED_BIDIRECTIONAL_ORDER_V1_0_H

#include <cassert>
#include <vector>
#include <limits>

namespace impl
{
  namespace list_array_enchanced
  {
    namespace v1_0
    {
      template <typename T>
      struct BidirectionalOrder
      {
	using index_t = T;
	static constexpr index_t null_ = std::numeric_limits<index_t>::max();
	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
      public:
	static constexpr
	index_t get_head() { return head; }
	static constexpr
	index_t get_tail() { return tail; }
      public:
	void push_back()
	{
	  index_t old_head = next[get_head()];
	  index_t node = next.size();

	  prev.push_back(get_head());
	  next.push_back(old_head);
	  prev[old_head] = node;
	  next[get_head()] = node;
	}
	index_t get_next(index_t node_)
	{
	  assert(node_ < next.size());
	  return next[node_];
	}
	void remove_node(index_t node)
	{
	  assert( node < next.size());
	  assert( node != get_head() );
	  assert( node != get_tail() );
	  
	  index_t& prev_node_next = next[prev[node]];
	  index_t& next_node_prev = prev[next[node]];
	  next_node_prev = prev[node];
	  prev_node_next = next[node];

	  move_last_to(node);
	  next.pop_back();
	  prev.pop_back();
	}
	void move_last_to(index_t node)
	{
	  assert( node < next.size());
	  assert( node != get_head() );
	  assert( node != get_tail() );

	  if(next.size()-1 == node) return;

	  index_t& prev_node_next = next[prev.back()];
	  index_t& next_node_prev = prev[next.back()];
	  prev_node_next = node;
	  next_node_prev = node;
	  prev[node] = prev.back();
	  next[node] = next.back();
	}
      private:
	static constexpr index_t head = 1;
	static constexpr index_t tail = 0;
	std::vector<index_t> next = { get_head(), get_tail() };
	std::vector<index_t> prev = { get_head(), get_tail() };
      };
    }
  }
}

#endif /* LIST_ARRAY_ENCHANCED_BIDIRECTIONAL_ORDER_V1_0_H */
