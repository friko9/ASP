#ifndef COMMON_H
#define COMMON_H

#include <ostream>
#include <limits>

template<size_t size>
union BigT
{
    template<size_t S>
    friend bool operator < ( const BigT<S>& arg1, const BigT<S>& arg2 );
    template<size_t S>
    friend bool operator == ( const BigT<S>& arg1, const BigT<S>& arg2 );
    template<size_t S>
    friend bool operator != ( const BigT<S>& arg1, const BigT<S>& arg2 );
    template<size_t S>
    friend bool operator <= ( const BigT<S>& arg1, const BigT<S>& arg2 );
public:
    int val;
    char fill[size];
public:
    BigT() = default;
    BigT(const BigT&) = default;
    BigT(BigT&&) = default;
    BigT(BigT&) = default;
    BigT(int x):val(x){}
    BigT& operator = (const BigT& arg) = default;
    BigT& operator = (BigT& arg) = default;
    BigT& operator = (BigT&& arg) = default;
    BigT& operator ++ (){ ++val; return *this;} 
};

template<size_t size>
inline bool operator <  (const BigT<size>& arg1, const BigT<size>& arg2){ return arg1.val <  arg2.val; }
template<size_t size>
inline bool operator == (const BigT<size>& arg1, const BigT<size>& arg2){ return arg1.val == arg2.val; }
template<size_t size>
inline bool operator != (const BigT<size>& arg1, const BigT<size>& arg2){ return arg1.val != arg2.val; }
template<size_t size>
inline bool operator <= (const BigT<size>& arg1, const BigT<size>& arg2){ return arg1.val <= arg2.val; }

using T20B = BigT<20>;
using T128B = BigT<128>;

namespace std
{
    template<size_t size>
    inline ostream& operator << (ostream& o,BigT<size>& arg){ o<<arg.val; return o;}

    template <>
    class numeric_limits<T20B>
	: public numeric_limits<int>
    {    };

    template <>
    class numeric_limits<T128B>
	: public numeric_limits<int>
    {    };
}

#endif /*COMMON_H*/
