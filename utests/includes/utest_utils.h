#ifndef UTEST_UTILS_H
#define UTEST_UTILS_H

#include <algorithm>
#include <memory>
#include <exception>

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#ifndef UTEST_FNAME
// defined by cmake in compile-time
// if not defined - no action
#define UTEST_FNAME (void)
#endif

template <typename T>
class ResultSorted
{
  std::unique_ptr<T> sorted_result = nullptr;
public:
  void expected_result(T arg)  {
    std::stable_sort(begin(arg),end(arg));
    sorted_result = std::make_unique<T,T&&>(std::move(arg));
  }
  const T& expected_result() const  {
    if (!sorted_result) throw std::runtime_error("result not specified. Define result first");
    return *sorted_result; 
  }
};

#endif /*UTEST_UTILS_H*/
