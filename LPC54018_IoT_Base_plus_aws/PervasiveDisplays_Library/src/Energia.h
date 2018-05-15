#ifndef ENERGIA_H
#define ENERGIA_H

#include "board.h"
#include <stdbool.h>
#include <string>

typedef bool boolean;
typedef const char* String;

//#ifndef abs
//  #define abs(__x)  ((__x)<0 ? (-(__x)) : (__x))
//#endif

#ifndef map
  #define map(__x, __in_min, __in_max, __out_min, __out_max) \
		(((__x) - (__in_min)) * ((__out_max) - (__out_min)) / ((__in_max) - (__in_min)) + (__out_min))
#endif

#endif
