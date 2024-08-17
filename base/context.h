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

/* date = August 15th 2024 0:21 pm */

#ifndef BASE_CONTEXT_H
#define BASE_CONTEXT_H

#define DEBUG 1
#define UNIX_IS_LINUX 1
#define IGNORE_OS 0
#define IGNORE_COMPILER 0
#define IGNORE_LANG 0
#define IGNORE_CL_YEAR 0

/*
The generated macros from this file are:
- OS_WINDOWS
- OS_APPLE
- OS_LINUX
- OS_UNIX

- COMPILER_GCC
- COMPILER_CLANG
- COMPILER_CL
- COMPILER_TINYCC
- COMPILER_TURBOC
- COMPILER_CUIK

- LANG_C
- LANG_CPP

- COMPILER_CL_YEAR

- ARCH_X64
- ARCH_X86
- ARCH_ARM
- ARCH_ARM
*/

// MACROS
#ifndef DEBUG
#define DEBUG 0
#endif

// Get the operating system in use
#if defined(_WIN32) || defined(_WIN64) || defined(__NT__)
#define OS_WINDOWS 1
#elif __APPLE__
#define OS_APPLE 1
#elif __linux__
#define OS_LINUX 1
#elif __unix__
#define OS_UNIX 1
#else
#if !IGNORE_OS
#error Unknown operating system
#endif // !IGNORE_OS
#endif

// Unix and Linux are symilar to a point where you can
// write the same code for both.
#if OS_UNIX && UNIX_IS_LINUX
#define OS_LINUX 1
#endif

// Find out which compiler is in use
#ifdef __GNUC__
#define COMPILER_GCC 1
#elif __clang__
#define COMPILER_CLANG 1
#elif _MSC_VER
#define COMPILER_CL 1
#elif __TINYC__ 
#define COMPILER_TINYCC 1
#elif _TURBOC_
#define COMPILER_TURBOC 1
#elif __CUIK__
#define COMPILER_CUIK 1
#else
#if !IGNORE_COMPILER
#error Unknown compiler
#endif // !IGNORE_OS
#endif

// Find out if we are using C or C++
// CL doesnt define __STDC__ for some reason,
// so if it isn't C++ we assume it's C.
#ifdef __STDC__
#define LANG_C 1
#elif __cplusplus
#define LANG_CPP 1
#else
#if !IGNORE_LANG && !COMPILER_CL
#error Unknown C language
#else
#define LANG_C 1
#endif // !IGNORE_LANG && !COMPILER_CL
#endif

// Check CL compiler version
#if COMPILER_CL

#if _MSC_VER >= 1930
#define COMPILER_CL_YEAR 2022
#elif _MSC_VER >= 1920
#define COMPILER_CL_YEAR 2019
#elif _MSC_VER >= 1910
#define COMPILER_CL_YEAR 2017
#elif _MSC_VER >= 1900
#define COMPILER_CL_YEAR 2015
#elif _MSC_VER >= 1800
#define COMPILER_CL_YEAR 2013
#elif _MSC_VER >= 1700
#define COMPILER_CL_YEAR 2012
#elif _MSC_VER >= 1600
#define COMPILER_CL_YEAR 2010
#elif _MSC_VER >= 1500
#define COMPILER_CL_YEAR 2008
#elif _MSC_VER >= 1400
#define COMPILER_CL_YEAR 2005
#elif _MSC_VER >= 1200
#define COMPILER_CL_YEAR 6
#else
#define COMPILER_CL_YEAR 0
#endif

#else
/// If the compiler is not CL, we assume it has the newer C features.
#define COMPILER_CL_YEAR 2022
#endif

// Get the OS arch
// CL has different ARCH macros
#if COMPILER_CL

#ifdef _M_AMD64
#define ARCH_X64 1
#elif _M_I86
#define ARCH_X86 1
#elif _M_ARM
#define ARCH_ARM 1
#elif _M_ARM64
#define ARCH_ARM 1
#else
#error Unknown ARCH detextion
#endif

#else

#ifdef __amd64__
#define ARCH_X64 1
#elif __i386__
#define ARCH_X86 1
#elif __arm__
#define ARCH_ARM 1
#elif __aarch64__
#define ARCH_ARM64 1
#else
#error Unknown ARCH detextion
#endif

#endif

#endif //BASE_CONTEXT_H