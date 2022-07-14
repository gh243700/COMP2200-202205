#ifndef LIMITS_H
#define LIMITS_H
#include <limits.h>
#endif


#ifndef MACROS_H
#define MACROS_H

#define MAX(x, y) (((x) > (y)) ? (x) : (y)) 

#define MIN(x, y) (((x) > (y)) ? (y) : (x))

#define ABS(x) (((x) >= 0) ? (x) : (x) * -1)

#define RANGE(curr, min, max) for((curr) = (min); (curr) <= (max); (curr)++)

#define RANGE_DESC(curr, max, min) for((curr) = (max); (curr) >= (min); (curr)--) 

#define SET(ary, start, count, value)\
    do {                                        \
        size_t i;                               \
        size_t c = (count);                     \
        for(i = 0; i < c; i++) {                \
            *((ary) + (start) + i) = (value);   \
        }                                       \
    } while (0)                                 \
                            
#endif /* MACROS_H */
