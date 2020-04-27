#include <math.h>
#define TRUE            1
#define FALSE           0
#define BOOL            char
#define INDEX_NOT_FOUND -1
#define EPSILON         0.000001

BOOL short_equals (const void * a, const void * b);
BOOL int_equals   (const void * a, const void * b);
BOOL long_equals  (const void * a, const void * b);
BOOL double_equals(const void * a, const void * b);
