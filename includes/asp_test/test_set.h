#ifndef TEST_SET_H
#define TEST_SET_H

#include "./includes/utils/utils.h"

#include <signal.h>

#include <algorithm>
#include <exception>
#include <forward_list>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <memory>
#include <vector>
#include <deque>

#define TEST_INSERTER static test_inserter ins;
#define ENABLE_TEST(S,T) test_inserter T::ins = { S, new T}
#define DISABLE_TEST(S,T) test_inserter T::ins = { S, new TEST_DISABLED_<T>}

struct failed_list
{
    virtual std::string next_failed(){ return failed_end(); }
    std::string failed_end(){ return std::string(); }
};

template <typename T>
std::string tostring(T p)
{
    return std::to_string(p);
}

template <typename T,typename K>
std::string tostring(std::pair<T,K> p)
{
    return std::string("{")+tostring(p.first)+std::string(",")+tostring(p.second)+std::string("}");
}


template<typename T>
struct single_failed_list
    : public failed_list
{
    std::deque<T> failed_cases;
public:
    static std::shared_ptr<single_failed_list<T>> new_list()
	{ return std::make_shared<single_failed_list<T>>(); }
public:
    void add_failed(T arg)
	{
	    if( failed_cases.size() < 10 )
		failed_cases.push_back(arg);
	}
    std::string next_failed()
	{
	    if( failed_cases.empty() )
		return failed_end();
	    auto result = std::string("value = ")+tostring(failed_cases.front());
	    failed_cases.pop_front();
	    return result;
	}
};  

struct test_result
{
    struct dummy_fl_deleter_t
    {
	void operator() ( failed_list* ) const {};
    };
    static failed_list* dummy_fl()
	{
	    static failed_list singleton;
	    return &singleton;
	}
    
    long long int score;
    long long int max_score;
    std::shared_ptr<failed_list> fl = { dummy_fl(), dummy_fl_deleter_t() };
    test_result( int max = 0, int start_score = 0 )
	: score(start_score),max_score(max){}
    test_result( std::pair<int,int> test_score )
	: score(test_score.first),max_score(test_score.second){}
    test_result& operator ++ (){ ++score; return *this; }
    test_result& operator += (bool test)
	{ ++max_score; score += test; return *this; }
    std::shared_ptr<failed_list> get_failed() { return fl; }
    void set_failed(std::shared_ptr<failed_list> failed) { fl = failed; }
};

struct test_case
{
    virtual void configure(){}
    virtual test_result run() = 0;
    virtual ~test_case() = default;
};

template <typename T>
struct TEST_DISABLED_ : public test_case
{
    virtual test_result run(){ return { -1,-1 }; }
};

class test_set
{
    static constexpr const char* const c_red = "\e[31m";
    static constexpr const char* const c_null = "\e[37m";
    using ptr_t = test_case*;
    using cases_container_t = std::deque<std::pair<std::string,ptr_t>>;
    using results_container_t = std::map<std::string,test_result>;
    cases_container_t cases;
    results_container_t results;
    struct sigaction sig_act;
private:
    void intern_add_case(ptr_t tc,std::string name)
	{
	    cases.emplace_back(name,tc);
	}
    void intern_add_result(test_result tr,std::string name)
	{
	    results.emplace(name,tr);
	}
    static void segv_handler(int signum, siginfo_t *info, void *ptr)
	{
	    throw std::runtime_error("SEGV");
	}
    static test_result intern_run_test( test_case* tc )
	try
	{
	    tc->configure();
	    return tc->run();
	}catch( std::exception& e )
	{
	    std::cout<<"\n Test broken exception what()= "<<e.what()<<' ';
	    return { 0, -1 };
	}
    void intern_merge_cases( cases_container_t&& c)
	{
	    for( auto x : c )
		intern_add_case(x.second,x.first);
	    c.clear();
	}
    void intern_merge_results( results_container_t&& c)
	{
	    for( auto x : c )
		intern_add_result(x.second,x.first);
	    c.clear();
	}
public:
    test_set(){}
    void add_test(ptr_t c)
	{
	    intern_add_case(c,typeid(*c).name());
	}
    void merge( test_set&& c )
	{
	    intern_merge_cases( std::move(c.cases) );
	    intern_merge_results( std::move(c.results) );
	}
    test_set& operator +=(ptr_t c)
	{
	    add_test(c);
	    return *this;
	}
    test_set& operator <<(test_set&& c)
	{
	    merge( std::forward<test_set>(c) );
	    return *this;
	}
    
    void run()
	{
	    sig_act.sa_handler = (void(*)(int))segv_handler;
	    sig_act.sa_flags = SA_SIGINFO | SA_NODEFER;
	    sigaction(SIGSEGV,&sig_act,NULL);
	    while(!cases.empty())
	    {
		try{
		    auto it = cases.begin();
		    std::string test_name = it->first;
		    std::cout<<c_null<<test_name<<": "<<std::flush;
		    test_result res = intern_run_test(it->second);
		    intern_add_result(res,test_name);
		    if(res.score != res.max_score) std::cout<<c_red;
		    std::cout<<res.score<<'/'<<res.max_score<<std::endl;
		    cases.pop_front();
		} catch( std::exception& e )
		{
		    std::cout<<"\n Exception outside test what()= "<<e.what()<<' ';
		}
	    }
	    
	}
    void summary()
	{
	    std::cout<<"\n\n\n----------------------------------------\n\n";
	    int passed=0,overall=0;
	    std::string::size_type name_max =0;
	    for( auto c : results ) name_max = std::max(name_max,c.first.size());
	    for( auto c : results )
	    {
		++overall;
		auto res = c.second;
		bool ok = res.score == res.max_score && res.max_score > 0;
		passed += ok;
		if(ok) continue;
		std::cout<<((ok)? c_null : c_red);
		std::cout<<std::setw(name_max)<<std::right<<c.first<<": "<<((ok)? "passed":"failed")<<c_null<<'\n';
		auto failed = res.get_failed();
		for( std::string s = failed->next_failed(); !s.empty(); s = failed->next_failed() )
		    std::cout<<s<<'\n';
	    }
	    std::cout<<"----------------------------------------\n\n";
	    std::cout<<"Total tests passed: "<<passed<<'/'<<overall<<'\n';
	    std::cout<<std::endl<<std::endl;
	}
};

struct test_inserter
{
    test_inserter( test_set& ts, test_case* tc ){ ts += tc; }
};

#endif /* TEST_SET_H */

