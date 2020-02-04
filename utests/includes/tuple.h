#ifndef TUPLE_H
#define TUPLE_H

#include <vector>
#include <ostream>
#include <utility>
#include <tuple>

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
auto& to_vector_impl (std::vector<T1>& out, std::tuple<T1> arg)
{
  out.push_back(tuple_head(arg));
  return out;
}

template<typename T1,typename T2,typename ... Args >
auto& to_vector_impl (std::vector<T1>& out, std::tuple<T1,T2,Args...> arg)
{
  out.push_back(tuple_head(arg));
  return to_vector_impl(out,tuple_tail(arg));
}

template<typename ... Args>
auto to_vector (const std::tuple<Args...>& arg)
{
  using T = decltype(tuple_head(arg));
  std::vector<T> v;
  return to_vector_impl(v,arg);
}

template<typename T1>
std::ostream& print_tuple (std::ostream& out, std::tuple<T1> arg)
{
  return out<<tuple_head(arg);
}

template<typename T1,typename T2,typename ... Args >
std::ostream& print_tuple (std::ostream& out, std::tuple<T1,T2,Args...> arg)
{
  out<<tuple_head(arg)<<',';
  return print_tuple(out,tuple_tail(arg));
}

template<typename ... Args>
std::ostream& operator << (std::ostream& out,const std::tuple<Args...>& arg)
{
  out<<'{';
  print_tuple(out,arg);
  out<<'}';
  return out;
}

template<typename T>
std::ostream& operator << (std::ostream& out,const std::vector<T>& arg)
{
  out<<'{';
  for(T x : arg) out<<x<<',';
  out<<'}';
  return out;
}
#endif
