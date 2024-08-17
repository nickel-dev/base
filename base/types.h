// Copyright (c) 2024 Daniel Nickel
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include "context.h"
#include "macros.h"

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef uint8_t b8;
typedef uint16_t b16;
typedef uint32_t b32;
typedef uint64_t b64;

//**************************************************
// Sin/Cosine lookup table
//**************************************************
//global const f64 SIN_LOOKUP_TABLE[180] =
//{
//0.000000, 0.017452, 0.034899, 0.052336, 0.069756, 0.087156, 0.104528, 0.121869, 0.139173, 0.156434, 0.173648, 0.190809, 0.207912, 0.224951, 0.241922, 0.258819, 0.275637, 0.292372, 0.309017, 0.325568, 0.342020, 0.358368, 0.374607, 0.390731, 0.406737, 0.422618, 0.438371, 0.453990, 0.469472, 0.484810, 0.500000, 0.515038, 0.529919, 0.544639, 0.559193, 0.573576, 0.587785, 0.601815, 0.615661, 0.629320, 0.642788, 0.656059, 0.669131, 0.681998, 0.694658, 0.707107, 0.719340, 0.731354, 0.743145, 0.754710, 0.766044, 0.777146, 0.788011, 0.798636, 0.809017, 0.819152, 0.829038, 0.838671, 0.848048, 0.857167, 0.866025, 0.874620, 0.882948, 0.891007, 0.898794, 0.906308, 0.913545, 0.920505, 0.927184, 0.933580, 0.939693, 0.945519, 0.951057, 0.956305, 0.961262, 0.965926, 0.970296, 0.974370, 0.978148, 0.981627, 0.984808, 0.987688, 0.990268, 0.992546, 0.994522, 0.996195, 0.997564, 0.998630, 0.999391, 0.999848, 1.000000, 0.999848, 0.999391, 0.998630, 0.997564, 0.996195, 0.994522, 0.992546, 0.990268, 0.987688, 0.984808, 0.981627, 0.978148, 0.974370, 0.970296, 0.965926, 0.961262, 0.956305, 0.951057, 0.945519, 0.939693, 0.933580, 0.927184, 0.920505, 0.913545, 0.906308, 0.898794, 0.891007, 0.882948, 0.874620, 0.866025, 0.857167, 0.848048, 0.838671, 0.829038, 0.819152, 0.809017, 0.798636, 0.788011, 0.777146, 0.766044, 0.754710, 0.743145, 0.731354, 0.719340, 0.707107, 0.694658, 0.681998, 0.669131, 0.656059, 0.642788, 0.629320, 0.615661, 0.601815, 0.587785, 0.573576, 0.559193, 0.544639, 0.529919, 0.515038, 0.500000, 0.484810, 0.469472, 0.453990, 0.438371, 0.422618, 0.406737, 0.390731, 0.374607, 0.358368, 0.342020, 0.325568, 0.309017, 0.292372, 0.275637, 0.258819, 0.241922, 0.224951, 0.207912, 0.190809, 0.173648, 0.156434, 0.139173, 0.121869, 0.104528, 0.087156, 0.069756, 0.052336, 0.034899, 0.017452
//};
//
//#define fast_cos(d) fast_sin(d + 90)
//inline_function f64 fast_sin(i32 d)
//{
// normalize
//d = d % 360;
//
//if (d < 0)
//d += 360;
//
// sin(-x) = -sin(x)
//if (d >= 180)
//{
//d -= 180;
//return -SIN_LOOKUP_TABLE[d];
//}
//return SIN_LOOKUP_TABLE[d];
//}

typedef union
{
  struct { f32 one, two; };
  struct { f32 a, b; };
  struct { f32 x, y; };
  struct { f32 u, v; };
	
  f32 e[2];
  f32 elements[2];
} vec2_t;

typedef union
{
  struct { f32 one, two, three; };
  struct { f32 x, y, z; };
  struct { f32 r, g, b; };
  struct { f32 h, s, v; };
	
  struct { vec2_t xy; f32 _z1; };
	
  f32 e[3];
  f32 elements[3];
} vec3_t;

typedef union
{
  struct { f32 one, two, three, four; };
  struct { f32 x, y, z, w; };
  struct { f32 r, g, b, a; };
  struct { f32 h, s, v, _a1; };
	
  struct { vec2_t xy; vec2_t zw; };
  struct { vec3_t xyz; f32 _w1; };
	
  f32 e[4];
  f32 elements[4];
} vec4_t;

inline_function vec2_t vec2(f32 x, f32 y) { return (vec2_t){ x, y }; }
inline_function vec3_t vec3(f32 x, f32 y, f32 z) { return (vec3_t){ x, y, z }; }
inline_function vec4_t vec4(f32 x, f32 y, f32 z, f32 w) { return (vec4_t){ x, y, z, w }; }

inline_function vec2_t vec2_normalize(vec2_t v) { return vec2(normalize(v.x), normalize(v.y)); }
inline_function vec3_t vec3_normalize(vec3_t v) { return vec3(normalize(v.x), normalize(v.y), normalize(v.z)); }
inline_function vec4_t vec4_normalize(vec4_t v) { return vec4(normalize(v.x), normalize(v.y), normalize(v.z), normalize(v.w)); }

#define vec2_from_float(n) vec2(n, n)
#define vec3_from_float(n) vec3(n, n, n)
#define vec4_from_float(n) vec4(n, n, n, n)

#define __VECTOR_MATH_GEN(m)\
inline_function m(add, +)\
inline_function m(sub, -)\
inline_function m(mul, *)\
inline_function m(div, /)

#define __VEC2_V_MATH_STUB(n, o) vec2_t vec2_##n##_vec2(vec2_t a, vec2_t b) { return vec2(a.x o b.x, a.y o b.y); }
#define __VEC3_V_MATH_STUB(n, o) vec3_t vec3_##n##_vec3(vec3_t a, vec3_t b) { return vec3(a.x o b.x, a.y o b.y, a.z o b.z); }
#define __VEC4_V_MATH_STUB(n, o) vec4_t vec4_##n##_vec4(vec4_t a, vec4_t b) { return vec4(a.x o b.x, a.y o b.y, a.z o b.z, a.w o b.w); }

#define __VEC2_N_MATH_STUB(n, o) vec2_t vec2_##n##_float(vec2_t v, f32 x) { return vec2(v.x o x, v.y o x); }
#define __VEC3_N_MATH_STUB(n, o) vec3_t vec3_##n##_float(vec3_t v, f32 x) { return vec3(v.x o x, v.y o x, v.z o x); }
#define __VEC4_N_MATH_STUB(n, o) vec4_t vec4_##n##_float(vec4_t v, f32 x) { return vec4(v.x o x, v.y o x, v.z o x, v.w o x); }

__VECTOR_MATH_GEN(__VEC2_V_MATH_STUB)
__VECTOR_MATH_GEN(__VEC3_V_MATH_STUB)
__VECTOR_MATH_GEN(__VEC4_V_MATH_STUB)

__VECTOR_MATH_GEN(__VEC2_N_MATH_STUB)
__VECTOR_MATH_GEN(__VEC3_N_MATH_STUB)
__VECTOR_MATH_GEN(__VEC4_N_MATH_STUB)

#endif // BASE_TYPES_H