#ifndef __MACROS_H_
#define __MACROS_H_

#define array_size(a) (u64))(sizeof(a) / sizeof(a[0]))
#define foreach(name, array, type) for (type name = array; (name - array) < array_size(array); ++name)

#define MACRO_STR(x) #x
#define BREAK *(volatile char*)(NULL) = 0;

#define KILOBYTES(n) ((n) * 1024LL)
#define MEGABYTES(n) (KILOBYTES(n) * 1024LL)
#define GIGABYTES(n) (MEGABYTES(n) * 1024LL)
#define TERABYTES(n) (GIGABYTES(n) * 1024LL)

#define assert(cond, ...) do { if (!(bool)(cond)) {\
    printf("Assertion failed! file: '%s', line: %i.\nCondition: %s\nMessage: ", __FILE__, __LINE__, MACRO_STR(cond));\
    printf(__VA_ARGS__); BREAK\
}} while (0)

#endif // __MACROS_H_