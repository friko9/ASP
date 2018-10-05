#ifndef HASHSET_ARRAY_H
#define HASHSET_ARRAY_H

#include "includes/utils/utils.h"

#include <cassert>
#include <limits>
#include <vector>

template <typename T,typename HashF,typename RehashF>
class hashset_array
{
    friend TestPlug<hashset_array<T,HashF,RehashF>>;
    using index_t = typename std::vector<T>::size_type;
    using hash_t = typename std::make_unsigned<index_t>::type;
    static constexpr index_t null = std::numeric_limits<unsigned int>::max();
    std::vector<T> vals;
    std::vector<index_t> v_map;
    std::vector<index_t> v_cnt;
    float max_load;
    hash_t hash_max;
    index_t counter;
    index_t find(T x) const noexcept
	{
	    const hash_t h = hash(x);
	    index_t c = v_cnt[h];
	    if ( c != 0 )
	    {
		hash_t rh = h;
		for ( RehashF r; c != 0; rh = ((hash_t)r(x,rh))%hash_max)
		    if( v_map[rh] != null && h == hash(vals[v_map[rh]]) )
		    {
			--c;
			if ( vals[v_map[rh]] == x )
			    return rh;
		    }
	    }
	    return null;
	}
    void insert_hash(index_t index)
	{
	    const hash_t hash = hashset_array::hash(vals[index]);
	    hash_t rehash = hash;
	    for ( RehashF r; v_map[rehash] != null; rehash = ((hash_t)r(vals[index],rehash))%hash_max)
		;
	    v_map[rehash] = index;
	    ++v_cnt[hash];
	}
    void resize(index_t new_size)
	{
	    RehashF r;
	    std::vector<index_t> new_map(new_size,index_t(null));
	    std::vector<index_t> new_cnt(new_size,0);
	    swap(new_map,v_map);
	    swap(new_cnt,v_cnt);
	    hash_max = primes[floor_log2(v_map.size())];
	    counter = float(hash_max)*max_load - vals.size();

	    for( int i =0; i < vals.size(); ++i )
		insert_hash(i);
	}
    hash_t hash(T x) const noexcept { return ((hash_t)HashF()(x))%hash_max; }
public:
    hashset_array(float load=0.8,int size = 32): v_map(size,index_t(null)), v_cnt(size,0)
	{
	    max_load = load;
	    hash_max = primes[floor_log2(size)];
	    counter = float(hash_max)*max_load;
	}
    void insert(T x)
	{
	    if( counter == 0 ) resize(v_map.size()*2);
	    if( find(x) != null ) return;
	    index_t index = vals.size();
	    vals.push_back(x);
	    insert_hash(index);
	    --counter;
	}
    bool contains(T x) noexcept
	{
	    return find(x) != null;
	}
    void remove(T x) noexcept
	{
	    index_t hash = find(x);
	    if(hash == null) return;
	    index_t lasthash = find(vals.back());
	    assert(lasthash != null);
	    index_t index = v_map[hash];
	    std::swap( vals[index], vals.back());
	    v_map[lasthash] = index;
	    v_map[hash] = null;
	    --v_cnt[hashset_array::hash(x)];
	    
	    vals.pop_back();
	    ++counter;
	}
};

#endif /*HASHSET_ARRAY_H*/
