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

#ifndef BASE_IO_H
#define BASE_IO_H

#if OS_WINDOWS
#include <windows.h>
#endif

#undef APIENTRY
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "types.h"

inline_function char* read_file(const char* path)
{
  char* buffer;
  u64 length;
	
  FILE* file = fopen(path, "r");
  if (!file)
    return NULL;
	
  fseek (file, 0, SEEK_END);
  length = ftell(file);
  fseek (file, 0, SEEK_SET);
	
  buffer = (char*)calloc(1, (uint64_t)length);
  fread (buffer, 1, length, file);
  fclose (file);
	
  if (buffer)
    return buffer;
  return NULL;
}

inline_function b8 save_file(const char* path, const char* content)
{
	u64 length = strlen(content);
	
  FILE* file = fopen(path, "w");
  if (!file)
    return false;
	
  fprintf(file, content);
  fclose (file);
	
	return true;
}

// Dynamic libraries (DLLs at runtime)
#define GAME_ENTRY(name) void name(/**/)
typedef GAME_ENTRY(game_entry_t);

#define GAME_UPDATE_AND_RENDER(name) void name(/*game_memory *Memory, game_input *Input*/)
typedef GAME_UPDATE_AND_RENDER(game_update_and_render_t);

#define GAME_CLEANUP(name) void name(/**/)
typedef GAME_CLEANUP(game_cleanup_t);

// TODO - Implement dynamic libs for mac and linux
#if OS_WINDOWS
typedef struct
{
	b8 is_valid;
	game_entry_t *game_entry;
	game_update_and_render_t *game_update_and_render;
	game_cleanup_t *game_cleanup;
	
	// Win32
	HMODULE win32_dll;
} game_code_t;

inline_function game_code_t load_game_code(const char* source_dl, const char* temp_dl, char* lock_file_name)
{
	game_code_t result = { 0 };
	
	WIN32_FILE_ATTRIBUTE_DATA ignored;
	if (!GetFileAttributesEx(lock_file_name, GetFileExInfoStandard, &ignored))
	{
		CopyFile(source_dl, temp_dl, FALSE);
		result.win32_dll = LoadLibraryA(temp_dl);
		
		if (result.win32_dll)
		{
			result.game_entry = (game_update_and_render_t*)GetProcAddress(result.win32_dll, "game_entry");
			result.game_update_and_render = (game_update_and_render_t*)GetProcAddress(result.win32_dll, "game_update_and_render");
			result.game_cleanup = (game_update_and_render_t*)GetProcAddress(result.win32_dll, "game_cleanup");
			
			result.is_valid = (result.game_entry && result.game_update_and_render && result.game_cleanup);
		}
	}
	
	if (!result.is_valid)
	{
		result.game_entry = 0;
		result.game_update_and_render = 0;
		result.game_cleanup = 0;
	}
	
	return result;
}

inline_function void unload_game_code(game_code_t* game_code)
{
	if (game_code->win32_dll)
	{
		FreeLibrary(game_code->win32_dll);
		game_code->win32_dll = 0;
	}
	
	game_code->is_valid = false;
	game_code->game_entry = 0;
	game_code->game_update_and_render = 0;
	game_code->game_cleanup = 0;
}
#else
#error Dynamic libraries not implemented for this OS yet
#endif

#endif // BASE_IO_H