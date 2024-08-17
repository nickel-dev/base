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

#ifndef BASE_MEMORY_H
#define BASE_MEMORY_H

#include <stdarg.h>
#include "types.h"

inline_function char* string_format(const char* format, ...)
{
  va_list	ap;
	va_start(ap, format);
	
	i32 len = _vscprintf(format, ap);
  if (len < 0)
    return NULL;
	
  char* buffer = (char*)malloc((uint64_t)len + 1);
	
#ifdef STB_SPRINTF_H_INCLUDE
  if (stbsp_vsprintf(buffer, format, ap) < 0)
#else
  if (vsprintf(buffer, format, ap) < 0)
#endif
  {
    free((void*)buffer);
    return NULL;
  }
	
	va_end(ap);
  return buffer;
}

#endif // BASE_MEMORY_H