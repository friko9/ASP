#ifndef UTEST_TRAITS_H
#define UTEST_TRAITS_H

#include <gtest/gtest.h>
#include <iterator>

template<typename T>
struct std::iterator_traits<testing::internal::ParamIterator<T> >
{
  using difference_type = typename testing::internal::ParamIterator<T>::difference_type;
  using value_type = typename testing::internal::ParamIterator<T>::value_type;
  using pointer = void;
  using reference = typename testing::internal::ParamIterator<T>::reference;
  using iterator_category = std::forward_iterator_tag;
};

#endif /*UTEST_TRAITS_H*/
