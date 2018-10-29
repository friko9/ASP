#ifndef SORTING_H
#define SORTING_H

#include "includes/asp_test/test_set.h"

#include <limits>
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
	void populate_data_allvals_inorder()
	    {
		for(elem_t i =std::numeric_limits<elem_t>::min(); i < std::numeric_limits<elem_t>::max(); ++i)
		    data.push_back(i);
		data.push_back(std::numeric_limits<elem_t>::max());
	    }
    };

    template<typename T>
    test_result test_sorted(std::vector<T>& v)
    {
	test_result res = v.size()-1;
	if(v.size() <= 1) return {1,1};
	for(auto it1=v.begin(),it2=it1+1;it2!=v.end();++it1,++it2)
	    if( *it2 >= *it1 ) ++res;
	return res;
    }
}

#endif /*SORTING_H*/
