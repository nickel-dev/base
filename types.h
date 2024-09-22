#ifndef __TYPES_H_
#define __TYPES_H_

// NULL should always pe a nullptr
#undef NULL
#define NULL (void*)0x00000000

// Custom bool
#ifndef __cplusplus
#define __bool_true_false_are_defined 1
#define true 1
#define false 0
typedef _Bool bool;
#endif // __cplusplus

typedef float f32;
typedef double f64;

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef struct string {
    char* data;
    u64 size;
} string;

typedef struct Arena {
    void* start;
    u64 offset;
    u64 size;
} Arena;

#define intern static
#define persist static
#define global static

#endif // __TYPES_H_