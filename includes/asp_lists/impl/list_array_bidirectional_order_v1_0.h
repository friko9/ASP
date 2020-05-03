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
	static constexpr index_t null_ = std::numeric_limits<index_t>::max();

	static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value,
		       "Index types mismatch." );
      public:
	void move_elem(index_t src,index_t dst)
	{
	  assert(src < next_.size());
	  assert(dst < next_.size());
	  if(src == dst) return;

	  index_t& src_prev_next = (prev_[src] != null_)? next_[prev_[src]] : head_;
	  index_t& src_next_prev = (next_[src] != null_)? prev_[next_[src]] : tail_;
	  src_prev_next = src_next_prev = dst;
	  next_[dst] = next_[src];
	  prev_[dst] = prev_[src];
	}
	void exclude_elem(index_t node)
	{
	  assert(node < next_.size());
	  index_t& node_prev_next = (prev_[node] != null_)? next_[prev_[node]] : head_;
	  index_t& node_next_prev = (next_[node] != null_)? prev_[next_[node]] : tail_;
	  node_prev_next = next_[node];
	  node_next_prev = prev_[node];
	}
	void push_new_head()
	{
	  index_t prev_node = null_;
	  index_t new_head = next_.size();
	  index_t old_head = head_;
	  if( old_head != null_)
	    prev_[old_head] = new_head;
	  
	  head_ = new_head;
	  next_.push_back(old_head);
	  prev_.push_back(prev_node);
	}
	void pop_back() noexcept
	{
	  next_.pop_back();
	  prev_.pop_back();
	}
	index_t get_head(){return head_;}
	index_t get_next(index_t arg)
	{
	  assert(arg < next_.size());
	  return next_[arg];
	}
      private:
	index_t head_ = null_;
	index_t tail_ = 0;
	std::vector<index_t> next_;
	std::vector<index_t> prev_;
      };
    }
  }
}

#endif /* LIST_ARRAY_BIDIRECTIONAL_ORDER_V1_0_H */
