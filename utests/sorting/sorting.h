#ifndef SORTING_H
#define SORTING_H

#include "includes/asp_test/test_set.h"

#include <exception>
#include <limits>
#include <functional>
#include <vector>

namespace sorting
{
    test_set& access_test_set();
    
    struct sorting_test_case
	: public test_case
    {
    	using elem_t = int8_t;
	std::vector<elem_t> data;
    public:
	static std::vector<elem_t> allvals_inorder()
	    {
		std::vector<elem_t> ret;
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    ret.push_back(i);
		ret.push_back(std::numeric_limits<elem_t>::max());
		return ret;
	    }
	static std::vector<elem_t> doublevals_inorder()
	    {
		std::vector<elem_t> ret;
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    ret.push_back(i);
		    ret.push_back(i);
		}
		ret.push_back(std::numeric_limits<elem_t>::max());
		ret.push_back(std::numeric_limits<elem_t>::max());
		return ret;
	    }
	static std::vector<elem_t> multiple_same_val()
	    {
		std::vector<elem_t> ret;
		for( int i=0; i < 100; ++i)
		    ret.push_back(10);
		return ret;
	    }
	static test_result compare_test( const std::vector<elem_t> v1,
					 const std::vector<elem_t> v2,
					 std::function<bool(elem_t,elem_t)> is_equal = std::equal_to<elem_t>())
	    {
		if(v1.size() != v2.size()) throw std::logic_error("result size mismatch");

		test_result res;
		for(auto it1=v1.begin(),it2=v2.begin();it1!=v1.end();++it1,++it2)
		    res += is_equal(*it1,*it2);
		return res;
	    }
    };
	
}

#endif /*SORTING_H*/
