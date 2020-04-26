#ifndef HASHSET_BUCKET_H
#define HASHSET_BUCKET_H

#include "includes/utils/utils.h"

#include <cassert>
#include <forward_list>
#include <vector>

template <typename T,typename HashF>
class hashset_bucket
{
    friend TestPlug<hashset_bucket<T,HashF>>;
    using bucket_t = std::forward_list<T>;
    using index_t = typename std::vector<bucket_t>::size_type;
    using hash_t = typename std::make_unsigned<index_t>::type;
public:
    using elem_t = T;
public:
    hashset_bucket(float load=0.8,int size = 32): v_map(size)
	{
	    assert(load > 0.01);
	    max_load = load;
	    hash_max = primes[floor_log2(size)];
	    counter = float(hash_max)*max_load;
	}
    void insert(T x)
	{
	    if( counter == 0 ) resize(v_map.size()*2);
	    int hash = find(x);
	    for( T v : v_map[hash] )
		if( v == x ) return;
	    v_map[hash].push_front(x);
	    --counter;
	}
    bool contains(T x) noexcept
	{
	    for( T v : v_map[find(x)] )
		if( v == x ) return true;
	    return false;
	}
    void remove(T x) noexcept
	{
	    int hash = find(x);
	    v_map[hash].remove_if([this,x](T v){
		    if( x != v ) return false;
		    this->counter += 1;
		    return true;
		});
	}
private:
    index_t find(T x) noexcept
	{
	    HashF h;
	    hash_t hash = h(x);
	    return hash % hash_max;
	}
    void resize(index_t new_size)
	{
	    assert(new_size > 0);
	    std::vector<bucket_t> new_map(new_size);
	    swap(new_map,v_map);
	    hash_max = primes[floor_log2(v_map.size())];
	    counter = float(hash_max)*max_load;

	    for( index_t i =0; i < new_map.size(); ++i )
		for( auto v : new_map[i])
		{
		    v_map[find(v)].push_front(v);
		    --counter;
		}
	}
private:
    std::vector<bucket_t> v_map;
    float max_load;
    hash_t hash_max;
    index_t counter;
};

#endif /*HASHSET_BUCKET_H*/
