#ifndef COMMON_H
#define COMMON_H

#include <ostream>

namespace testspace
{
    
    union T20B
    {
	friend bool operator <  ( const T20B& arg1, const T20B& arg2 );
	friend bool operator == ( const T20B& arg1, const T20B& arg2 );
	friend bool operator != ( const T20B& arg1, const T20B& arg2 );
	friend bool operator <= ( const T20B& arg1, const T20B& arg2 );
    public:
	int val;
	char fill[20];
    public:
	T20B() = default;
	T20B(const T20B&) = default;
	T20B(T20B&&) = default;
	T20B(T20B&) = default;
	T20B(int x):val(x){}
	T20B& operator = (const T20B& arg) = default;
	T20B& operator = (T20B& arg) = default;
	T20B& operator = (T20B&& arg) = default;
	T20B& operator ++ (){ ++val; return *this;} 
    };

    bool operator <  (const T20B& arg1, const T20B& arg2){ return arg1.val <  arg2.val; }
    bool operator == (const T20B& arg1, const T20B& arg2){ return arg1.val == arg2.val; }
    bool operator != (const T20B& arg1, const T20B& arg2){ return arg1.val != arg2.val; }
    bool operator <= (const T20B& arg1, const T20B& arg2){ return arg1.val <= arg2.val; }
}

namespace std
{
    ostream& operator << (ostream& o,testspace::T20B& arg){ o<<arg.val; return o;}

    template <>
    class numeric_limits<testspace::T20B>
	: public numeric_limits<int>
    {    };
}
#endif COMMON_H
