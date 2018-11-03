#ifndef COMMON_H
#define COMMON_H

#include "../common.h"

#define named_pair(X,T) std::make_pair(string(#X"<")+typeid(T).name()+string(">"),(X<T>))

#endif COMMON_H
