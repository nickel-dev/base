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

/* date = August 15th 2024 3:06 pm */

#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#include <stdio.h>
#include <time.h>
#include "context.h"
#include "types.h"

#define M_PI 3.1415926

#define string_concat(a, b) (a ## b)

#define to_string(x) #x
#define to_bool(x) (x != 0)

#define array_len(x) (sizeof(x) / sizeof(*x))
#define memory_zero(p, s) memset(p, 0, s);

#define normalize(x) (1.0f / x)
#define average(x, y) ((f32)(x + y) / 2)

#define clamp(x, a, b) ((x < a) ? a : (x > b) ? b : x)

#define deg_to_rad(d) ((f32)d * (M_PI / 180.0))
#define rad_to_deg(r) (180.0 * r / PI)

#define assert_break() (*(volatile int*)0 = 0)

#if DEBUG
#define assert(c) do { if (!c) assert_break(); } while (0)
#else
#define assert(c)
#endif

#ifdef LANG_CPP
#define linkage extern "C"
#else
#define linkage extern
#endif

#define global static
#define local_persist static
#define function static

#if COMPILER_CL && COMPILER_CL_YEAR < 2015
#define inline_function function
#else
#define inline_function inline function
#endif

#if OS_WINDOWS
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT linkage
#endif

#define COLORED_LOGS false
#define LOG_COLOR_RED 91
#define LOG_COLOR_YELLOW 93
#define LOG_COLOR_GREEN 92
#define LOG_COLOR_CYAN 96
#define LOG_COLOR_BLUE 94
#define LOG_COLOR_MAGENTA 95

#if COLORED_LOGS
#define colored_log(c, ...) do { printf("\033[%sm", to_string(c)); log(__VA_ARGS__); printf("\033[97m\033[40m"); } while (0) 
#else
#define colored_log(c, ...) log(__VA_ARGS__)
#endif

#if DEBUG
#define log_assert(c, ...) do { if (!c) log_throw(__VA_ARGS__); } while (0)
#else
#define log_assert(c, ...) do { if (!c) log_error(__VA_ARGS__); } while (0)
#endif

#define log(...) fprintf(stdout, "[%llu] %s", time(0), __VA_ARGS__)
#define log_throw(...) do { log_error(__VA_ARGS__); assert_break(); } while (0)
#define log_error(...) colored_log(LOG_COLOR_RED, __VA_ARGS__)
#define log_warning(...) colored_log(LOG_COLOR_YELLOW, __VA_ARGS__)

#endif //BASE_MACROS_H