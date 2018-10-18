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
    using hash_t = index_t;
    static_assert( std::is_same<index_t,typename std::vector<index_t>::size_type>::value );
private:
    static constexpr index_t null = std::numeric_limits<index_t>::max();
private:
    std::vector<T> vals;
    std::vector<index_t> v_map;
    std::vector<index_t> v_cnt;
    float max_load;
    hash_t hash_max;
    index_t counter;
private:
    hash_t hashf(T x) 
	{ return hash_t(HashF()(x)) %hash_max; }
    hash_t rehashf(RehashF& rehasher,T x,hash_t hash) 
     	{ return hash_t(rehasher(x,hash)) %hash_max; }
    hash_t get_hashmax( index_t sizemax ) 
	{ return primes[floor_log2(sizemax)]; }
    index_t find(T x) 
	{
	    if(vals.empty()) return null;
	    const hash_t hash = hashf(x);
	    index_t counter = v_cnt[hash];
	    hash_t rehash = hash;
	    for ( RehashF rehasher; counter > 0; rehash = rehashf(rehasher,x,rehash) )
		if( v_map[rehash] != null && hash == hashf(vals[v_map[rehash]]) )
		{
		    --counter;
		    if ( vals[v_map[rehash]] == x )
			return rehash;
		}
	    return null;
	}
    void insert_hash(index_t index)
	{
	    const hash_t hash = hashf(vals[index]);
	    RehashF rehasher;
	    hash_t rehash = hash;
	    while( v_map[rehash] != null )
		rehash = rehashf(rehasher,vals[index],rehash);
	    v_map[rehash] = index;
	    ++v_cnt[hash];
	}
    void resize(index_t new_size)
	{
	    assert(new_size >= vals.size());
	    RehashF r;
	    std::vector<index_t> new_map(new_size,index_t(null));
	    std::vector<index_t> new_cnt(new_size,0);
	    swap(new_map,v_map);
	    swap(new_cnt,v_cnt);
	    hash_max = get_hashmax( v_map.size() );
	    assert(hash_max >= vals.size());
	    counter = index_t(float(hash_max)*max_load) - vals.size();

	    for( index_t i =0; i < vals.size(); ++i )
		insert_hash(i);
	}
    
public:
    hashset_array(float load=0.8,int size = 32): v_map(size,index_t(null)), v_cnt(size,0)
	{
	    max_load = load;
	    hash_max = get_hashmax( size );
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
	    --v_cnt[hashf(x)];
	    
	    vals.pop_back();
	    ++counter;
	}
};

#endif /*HASHSET_ARRAY_H*/
