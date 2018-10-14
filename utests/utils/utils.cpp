#include "includes/asp_test/test_set.h"
#include "includes/utils/utils.h"

#include <cmath>
#include <limits>
#include <utility>

struct test_primes_are_primes
    : public test_case
{
    test_result run()
	{
	    test_result result = sizeof(primes)/sizeof(int);
	    auto failed_list = single_failed_list<std::pair<int,int>>::new_list();
	    result.set_failed(failed_list);
	    for(int x : primes)
	    {
		int sqrt_x = sqrt(x);
		for( int i=2; i<=sqrt_x; ++i)
		    if( x%i == 0 )
		    {
			failed_list->add_failed( std::make_pair(x,i) );
			goto noscore;
		    }
		++result;
	    noscore:
		(void) 0;
	    }
	    return result;
	}
};

struct test_floor_log2_1_all_integers
    : public test_case
{
    test_result run()
	{
	    test_result result;
	    auto failed_list = single_failed_list<std::pair<uint32_t,uint32_t>>::new_list();
	    result.set_failed(failed_list);

	    for(uint32_t i=1; i > 0; ++i)
	    {
		bool res_ok = floor_log2_1(i) == uint32_t(log2(i));
		result += res_ok;
		if( !res_ok )
		    failed_list->add_failed( {i, floor_log2_1(i)} );
	    }
	    return result;
	}
};

struct test_floor_log2_3_all_integers
    : public test_case
{
    test_result run()
	{
	    test_result result;
	    auto failed_list = single_failed_list<std::pair<uint32_t,uint32_t>>::new_list();
	    result.set_failed(failed_list);

	    for(uint32_t i=1; i > 0; ++i)
	    {
		bool res_ok = floor_log2_3(i) == uint32_t(log2(i));
		result += res_ok;
		if( !res_ok )
		    failed_list->add_failed( {i, floor_log2_3(i)} );
	    }
	    return result;
	}
};

int main()
{
    test_set utils;
    utils += new test_primes_are_primes;
    utils += new test_floor_log2_1_all_integers;
    utils += new test_floor_log2_3_all_integers;

    utils.run();
    utils.summary();
}
