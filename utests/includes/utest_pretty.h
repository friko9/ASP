#ifndef UTEST_PRETTY_H
#define UTEST_PRETTY_H

#include <vector>
#include <string>
#include <tuple>
#include <gtest/gtest.h>

template <typename T, template<typename...> class ContainerT>
struct Pretty : public std::vector<T>
{
  using value_type = T;
  Pretty():
    std::vector<T>(),name("EmptyRange")
  {}
  template<template<typename...> class C>
  explicit Pretty(const C<T>& arg):
    std::vector<T>(arg.begin(),arg.end()),name("Range")
  {
    auto begin = arg.begin();
    auto next = ++arg.begin();
    auto end = arg.end();

    if(begin == end) return;
    std::tie(first_,last_,stride_) = std::make_tuple(*begin,*begin,T{});
    if(next == end) return;

    auto last = begin;
    for(auto it = next; it != end; ++it) ++last;
    std::tie(first_,last_,stride_) = std::make_tuple(*begin,*last,*next-*begin);
  }
  std::string toString() const
  {
    return { name
	     + "(first=" + to_string(first_)
	     + ",last=" + to_string(last_)
	     + ",stride=" + to_string(stride_)
	     + ")" };
  }
protected:
  std::string name;
private:
  T first_  {};
  T stride_  {};
  T last_  {};
};

template <typename T, template<typename...> class ContainerT>
struct ShuffledPretty : public Pretty<T,ContainerT>
{
  template<template<typename...> class C>
  explicit ShuffledPretty(const C<T>& arg):Pretty<T,ContainerT>(arg)
  {
    random_shuffle(this->begin(),this->end());
    this->name = "ShuffledRange";
  }
};

template <typename T, template<typename...> class ContainerT>
struct ReversePretty : public Pretty<T,ContainerT>
{
  template<template<typename...> class C>
  explicit ReversePretty(const C<T>& arg):Pretty<T,ContainerT>(arg)
  {
    reverse(this->begin(),this->end());
    this->name = "ReverseRange";
  }
};


template <typename T, template<typename...> class ContainerT, typename... Args>
Pretty<T,ContainerT> make_Pretty(ContainerT<T,Args...> arg) {
  return Pretty<T,ContainerT>{arg};
}

template <typename T, template<typename...> class ContainerT>
ShuffledPretty<T,ContainerT> make_ShuffledPretty(ContainerT<T> arg) {
  return ShuffledPretty<T,ContainerT>{arg};
}

template <typename T, template<typename...> class ContainerT>
ReversePretty<T,ContainerT> make_ReversePretty(ContainerT<T> arg) {
  return ReversePretty<T,ContainerT>{arg};
}

template <typename T, template<typename> class ContainerT>
class testing::internal::UniversalTersePrinter<Pretty<T,ContainerT>> {
public:
  static void Print(const Pretty<T,ContainerT>& obj, ::std::ostream* os) {
    *os << obj.toString();
  }
};


#endif /*UTEST_PRETTY_H*/
