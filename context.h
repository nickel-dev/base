#ifndef __CONTEXT_H_
#define __CONTEXT_H_

#ifdef _WIN32
#define OS_WINDOWS 1
#elif __gnu_linux__
#define OS_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
#define OS_MAC 1
#else
#error Unknown operating system
#endif

#if defined(__amd64__) || defined(_M_AMD64)
#define ARCH_X64 1
#elif defined(__i386__) || defined(_M_I86)
#define ARCH_X86 1
#elif defined(__arm__) || defined(_M_ARM)
#define ARCH_ARM 1
#elif defined(__aarch64__)
#define ARCH_ARM64 1
#else
#error Unknown chip archetype
#endif

#if OS_WINDOWS
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#error OS currently not supported
#endif

void* malloc(size_t size);
void free(void* p);
int printf(const char* fmt, ...);
void* memcpy(void* dest, const void* src, size_t count);

#endif // __CONTEXT_H_