#ifndef TUPLE_H

#include <vector>
#include <ostream>
#include <utility>
#include <tuple>

using std::enable_if;
using std::ostream;
using std::tuple;
using std::vector;

template < typename T , typename... Ts >
auto tuple_head( std::tuple<T,Ts...> t )
{
   return  std::get<0>(t);
}

template < std::size_t... Ns , typename... Ts >
auto tuple_tail_impl( std::index_sequence<Ns...> , std::tuple<Ts...> t )
{
   return  std::make_tuple( std::get<Ns+1u>(t)... );
}

template < typename... Ts >
auto tuple_tail( std::tuple<Ts...> t )
{
   return  tuple_tail_impl( std::make_index_sequence<sizeof...(Ts) - 1u>() , t );
}

template<typename T1>
ostream& print_tuple (ostream& out,const tuple<T1>& arg)
{
  return out<<tuple_head(arg);
}

template<typename T1,typename T2,typename ... Args >
ostream& print_tuple (ostream& out,const tuple<T1,T2,Args...>& arg)
{
  out<<tuple_head(arg)<<',';
  return print_tuple(out,tuple_tail(arg));
}

template<typename ... Args>
ostream& operator << (ostream& out,const tuple<Args...>& arg)
{
  out<<'{';
  print_tuple(out,arg);
  out<<'}';
  return out;
}

template<typename T>
ostream& operator << (ostream& out,const vector<T>& arg)
{
  out<<'{';
  for(T x : arg) out<<x<<',';
  out<<'}';
  return out;
}
#endif
