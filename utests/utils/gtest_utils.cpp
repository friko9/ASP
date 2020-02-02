#include "utils.h"
#include <gtest/gtest.h>

#include <cmath>
#include <limits>
#include <utility>

using namespace ::testing;
using namespace ::std;
class utest_floor_log2_1 : public ::testing::WithParamInterface<pair<uint32_t,uint32_t>>, public ::testing::Test
{};
class utest_floor_log2_3 : public ::testing::WithParamInterface<pair<uint32_t,uint32_t>>, public ::testing::Test
{};
class utest_floor_log2 : public ::testing::WithParamInterface<pair<uint32_t,uint32_t>>, public ::testing::Test
{};
class utest_primes : public ::testing::WithParamInterface<int>, public ::testing::Test
{};

TEST_P(utest_floor_log2_1, _equals_floor_log2 )
{
  uint32_t result_l = floor_log2_1(GetParam().first);
  uint32_t result_u = floor_log2_1(GetParam().second);
  ASSERT_EQ( result_l, result_u);
  ASSERT_EQ( result_l, floor(log2(GetParam().first)) );
}
TEST_P(utest_floor_log2, _equals_floor_log2 )
{
  uint32_t result_l = floor_log2_1(GetParam().first);
  uint32_t result_u = floor_log2_1(GetParam().second);
  ASSERT_EQ( result_l, result_u);
  ASSERT_EQ( result_l, floor(log2(GetParam().first)) );
}
TEST_P(utest_floor_log2_3, _equals_floor_log2 )
{
  uint32_t result_l = floor_log2_1(GetParam().first);
  uint32_t result_u = floor_log2_1(GetParam().second);
  ASSERT_EQ( result_l, result_u);
  ASSERT_EQ( result_l, floor(log2(GetParam().first)) );
}

constexpr pair<uint32_t,uint32_t> small_ints[] = { {0x01,0x01},{0x02,0x03},{0x04,0x07},{0x08,0x0F},{0x10,0x1F},{0x20,0x3F},{0x40,0x7F},{0x80,0xFF} };
constexpr pair<uint32_t,uint32_t> medium_ints[] = { {0x0100,0x01FF},{0x0200,0x03FF},{0x0400,0x07FF},{0x0800,0x0FFF},{0x1000,0x1FFF},{0x2000,0x3FFF},
						    {0x4000,0x7FFF},{0x8000,0xFFFF} };
constexpr pair<uint32_t,uint32_t> large_ints[] = { {0x010000,0x01FFFF},{0x020000,0x03FFFF},{0x040000,0x07FFFF},{0x080000,0x0FFFFF},{0x100000,0x1FFFFF},
						   {0x200000,0x3FFFFF},{0x400000,0x7FFFFF},{0x800000,0xFFFFFF} };
constexpr pair<uint32_t,uint32_t> huge_ints[] = { {0x01000000,0x01FFFFFF},{0x02000000,0x03FFFFFF},{0x04000000,0x07FFFFFF},{0x08000000,0x0FFFFFFF}
						  ,{0x10000000,0x1FFFFFFF},{0x20000000,0x3FFFFFFF},{0x40000000,0x7FFFFFFF},{0x80000000,0xFFFFFFFF} };

INSTANTIATE_TEST_CASE_P(small_integers, utest_floor_log2_1, ValuesIn(small_ints) );
INSTANTIATE_TEST_CASE_P(mid_integers, utest_floor_log2_1, ValuesIn(medium_ints) );
INSTANTIATE_TEST_CASE_P(large_integers, utest_floor_log2_1, ValuesIn(large_ints) );
INSTANTIATE_TEST_CASE_P(huge_integers, utest_floor_log2_1, ValuesIn(huge_ints) );

INSTANTIATE_TEST_CASE_P(small_integers, utest_floor_log2_3, ValuesIn(small_ints) );
INSTANTIATE_TEST_CASE_P(mid_integers, utest_floor_log2_3, ValuesIn(medium_ints) );
INSTANTIATE_TEST_CASE_P(large_integers, utest_floor_log2_3, ValuesIn(large_ints) );
INSTANTIATE_TEST_CASE_P(huge_integers, utest_floor_log2_3, ValuesIn(huge_ints) );

INSTANTIATE_TEST_CASE_P(small_integers, utest_floor_log2, ValuesIn(small_ints) );
INSTANTIATE_TEST_CASE_P(mid_integers, utest_floor_log2, ValuesIn(medium_ints) );
INSTANTIATE_TEST_CASE_P(large_integers, utest_floor_log2, ValuesIn(large_ints) );
INSTANTIATE_TEST_CASE_P(huge_integers, utest_floor_log2, ValuesIn(huge_ints) );

TEST_P(utest_primes,has_no_divisors)
{
  auto test_subject = GetParam();
  for(int i=3;i<(sqrt(test_subject)+1);i+=2)
    ASSERT_NE( (test_subject % i), 0 );
}

INSTANTIATE_TEST_CASE_P(primes, utest_primes, ValuesIn(primes) );
