#include "includes/asp_test/test_set.h"
#include "includes/utils/utils.h"
#include <cmath>
#include <limits>
#include <set>
#include <sstream>
#include <string>

namespace std
{
    std::string to_string( std::string arg ) 
    {
	return arg;
    }
}


using namespace std;

#define PRINT_RESULT(X) (std::string(#X " = ") + to_string(X))

struct test_primes_are_primes : public test_case
{
    vector<pair<int,int>> failed_cases;
    vector<pair<int,int>>::size_type index =0;
    std::string next_failed()
	{
	    int i = index++;
	    if( i >= failed_cases.size() )
		return std::string();
	    stringstream ss;
	    ss <<'['<< i <<"]: prime ="<< to_string(failed_cases.at(i).first);
	    ss <<", divisor = "<< to_string(failed_cases.at(i).first);
	    return ss.str();
	}
    test_result run()
	{
	    test_result result = sizeof(primes)/sizeof(int);
	    for(int x : primes)
	    {
		int sqrt_x = sqrt(x);
		for( int i=2; i<=sqrt_x; ++i)
		    if( x%i == 0)
		    {
			failed_cases.emplace_back(x,i);
			goto noscore;
		    }
		++result;
	    noscore:
		(void) 0;
	    }
	    return result;
	}
};

struct test_floor_log2_1_all_integers : public test_case
{
    vector<int> failed_cases;
    vector<int>::size_type index =0;
    
    std::string next_failed()
	{
	    int i = index++;
	    if( i >= failed_cases.size() )
		return std::string();
	    stringstream ss;
	    ss <<'['<< i <<"]: " << PRINT_RESULT( floor_log2_1(failed_cases.at(i)) );
	    ss << PRINT_RESULT( int( log2(failed_cases.at(i)) ) );
	    return ss.str();
	}
    test_result run()
	{
	    test_result result = numeric_limits<int>::max();
	    for(int i=0; i >= 0; ++i)
	    {
		if( floor_log2_1(i) != int(log2(i)))
		{
		    if(failed_cases.size() < 100 )
			failed_cases.emplace_back(i);
		}
		else
		    ++result;
	    }
	    return result;
	}
};

struct test_floor_log2_3_all_integers : public test_case
{
    vector<int> failed_cases;
    vector<int>::size_type index =0;
    
    std::string next_failed()
	{
	    int i = index++;
	    if( i >= failed_cases.size() )
		return std::string();
	    stringstream ss;
	    ss <<'['<< i <<"]: " << PRINT_RESULT( floor_log2_3(failed_cases.at(i)) );
	    ss << PRINT_RESULT( int( log2(failed_cases.at(i)) ) );
	    return ss.str();
	}
    test_result run()
	{
	    test_result result = numeric_limits<int>::max();
	    for(int i=0; i >= 0; ++i)
	    {
		if( floor_log2_3(i) != int(log2(i)))
		{
		    if(failed_cases.size() < 100 )
			failed_cases.emplace_back(i);
		}
		else
		    ++result;
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
