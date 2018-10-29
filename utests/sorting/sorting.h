#ifndef SORTING_H
#define SORTING_H

#include "includes/asp_test/test_set.h"

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
	static test_result test_sorted(std::vector<elem_t>& v,
				       std::function<bool(const elem_t,const elem_t)> cmp_in_order = std::less<elem_t>())
	    {
		test_result res = v.size()-1;
		if(v.size() <= 1) return {1,1};
		for(auto it1=v.begin(),it2=it1+1;it2!=v.end();++it1,++it2)
		    if( cmp_in_order(*it1,*it2) ) ++res;
		return res;
	    }
    public:
	void populate_data_allvals_inorder()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
	void populate_data_doublevals_inorder()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		{
		    data.push_back(i);
		    data.push_back(i);
		}
		data.push_back(std::numeric_limits<elem_t>::max());
		data.push_back(std::numeric_limits<elem_t>::max());
	    }

    };
}

#endif /*SORTING_H*/
