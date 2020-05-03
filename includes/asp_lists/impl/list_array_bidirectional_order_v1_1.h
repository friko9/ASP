#ifndef LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_1_H
#define LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_1_H

#include <cassert>
#include <vector>
#include <limits>

namespace impl
{
  namespace list_array
  {    
    namespace v1_1
    {
      template <typename T>
      struct BidirectionalOrder
      {
	using index_t = T;
	static constexpr index_t null = std::numeric_limits<index_t>::max();

	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
      public:
	void remove_node(index_t node_arg) noexcept
	{
	  assert(node_arg < next.size());
	  index_t& node_prev_next = (prev[node_arg] != null)? next[prev[node_arg]] : head;
	  index_t& node_next_prev = (next[node_arg] != null)? prev[next[node_arg]] : tail;
	  node_prev_next = next[node_arg];
	  node_next_prev = prev[node_arg];

	  move_last_to(node_arg);
	  prev.pop_back();
	  next.pop_back();
	}
	void move_last_to(index_t node_arg) noexcept
	{
	  assert(node_arg < next.size());	  
	  if( next.size()-1 == node_arg) return;
	  index_t& src_prev_next = (prev.back() != null)? next[prev.back()] : head;
	  index_t& src_next_prev = (next.back() != null)? prev[next.back()] : tail;
	  src_prev_next = node_arg;
	  src_next_prev = node_arg;
	  prev[node_arg] = prev.back();
	  next[node_arg] = next.back();
	}
	void push_new_head()
	{
	  index_t new_head = next.size();
	  index_t old_head = head;
	  if( old_head != null)
	    prev[old_head] = new_head;
	  
	  head = new_head;
	  prev.push_back( index_t{null} );
	  next.push_back( old_head );
	}
	index_t get_head() const noexcept {return head;}
	index_t get_next(index_t node_arg) noexcept
	{
	  assert(node_arg < next.size());
	  return next[node_arg];
	}
      private:
	index_t head = null;
	index_t tail = 0;
	std::vector<index_t> next;
	std::vector<index_t> prev;
      };
    }
  }
}

#endif /* LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_1_H */
