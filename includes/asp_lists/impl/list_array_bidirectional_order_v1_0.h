#ifndef LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_0_H
#define LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_0_H

#include <cassert>
#include <vector>
#include <limits>

namespace impl
{
  namespace list_array
  {    
    namespace v1_0
    {
      template <typename T>
      struct BidirectionalOrder
      {
	using index_t = T;
	static constexpr index_t null = std::numeric_limits<index_t>::max();

	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
      public:
	void remove_node(index_t node_arg)
	{
	  index_t last = next.size()-1;
	  exclude_elem(node_arg);
	  move_elem(last,node_arg);
	  pop_back();
	}
	void move_elem(index_t src_arg,index_t dst_arg) noexcept
	{
	  assert(src_arg < next.size());
	  assert(dst_arg < next.size());
	  if(src_arg == dst_arg) return;

	  index_t& src_prev_next = (prev[src_arg] != null)? next[prev[src_arg]] : head;
	  index_t& src_next_prev = (next[src_arg] != null)? prev[next[src_arg]] : tail;
	  src_prev_next = dst_arg;
	  src_next_prev = dst_arg;
	  next[dst_arg] = next[src_arg];
	  prev[dst_arg] = prev[src_arg];
	}
	void exclude_elem(index_t node_arg) noexcept
	{
	  assert(node_arg < next.size());
	  index_t& node_prev_next = (prev[node_arg] != null)? next[prev[node_arg]] : head;
	  index_t& node_next_prev = (next[node_arg] != null)? prev[next[node_arg]] : tail;
	  node_prev_next = next[node_arg];
	  node_next_prev = prev[node_arg];
	}
	void push_new_head() noexcept
	{
	  index_t prev_node = null;
	  index_t new_head = next.size();
	  index_t old_head = head;
	  if( old_head != null)
	    prev[old_head] = new_head;
	  
	  head = new_head;
	  next.push_back(old_head);
	  prev.push_back(prev_node);
	}
	void pop_back() noexcept
	{
	  next.pop_back();
	  prev.pop_back();
	}
	index_t get_head(){return head;}
	index_t get_next(index_t node_arg)
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

#endif /* LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_0_H */
