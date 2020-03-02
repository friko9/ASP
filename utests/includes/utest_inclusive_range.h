#ifndef UTEST_INCLUSIVE_RANGE_H
#define UTEST_INCLUSIVE_RANGE_H

#include <vector>

template <typename T>
std::vector<T> make_InclusiveRange(T first,T last,T stride = T{1})
{
  std::vector<T> ret;
  for(T i=first; i < last; i += stride)
    ret.push_back(i);
  ret.push_back(last);
  return ret;
}

#endif /*UTEST_INCLUSIVE_RANGE_H*/
