#ifndef __IO_H_
#define __IO_H_

typedef enum File_Mode {
	FILE_MODE_READ = 1 << 0, FILE_MODE_WRITE = 1 << 1, FILE_MODE_CREATE = 1 << 2
} File_Mode;

#if OS_WINDOWS
typedef HANDLE File;
#else
#error File is currently no defined for your OS 
#endif

intern File file_open(const char* path, File_Mode modes);
intern inline void file_close(File f);
intern u64 file_get_size(File f);
intern inline bool file_read(File f, char* dest, u64 bytes_to_read, u64 actually_read);
intern inline bool file_read_to_string(File f, string* dest);

#if OS_WINDOWS

// source: https://github.com/alpinestudios/oogabooga/blob/00042a3607fd97f207c34145fa3e917e9143b047/oogabooga/os_impl_windows.c#L1025
intern u16*
win32_utf8_to_utf16(string utf8) {
	if (utf8.size == 0) {
		u16 *utf16_str = (u16*)HeapAlloc(GetProcessHeap(), 0, sizeof(u16));
		*utf16_str = 0;
		return utf16_str;
	}

    u64 utf16_length = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)utf8.data, (int)utf8.size, 0, 0);

    u16 *utf16_str = (u16*)HeapAlloc(GetProcessHeap(), 0, (utf16_length + 1) * sizeof(u16));

    int result = MultiByteToWideChar(CP_UTF8, 0, (LPCCH)utf8.data, (int)utf8.size, (LPWSTR)utf16_str, utf16_length);
    if (result == 0)
        return 0;

    utf16_str[utf16_length] = 0;

    return utf16_str;
}

intern File
file_open(const char* path, File_Mode modes) {
    DWORD access = GENERIC_READ;
    DWORD mode = 0;

    if (modes & FILE_MODE_WRITE)
        access |= GENERIC_WRITE;
    if (modes & FILE_MODE_CREATE)
        mode = CREATE_ALWAYS;
    else
        mode = OPEN_EXISTING;
    
    LPCWSTR filename = (LPCWSTR)win32_utf8_to_utf16(str(path));
    File f = CreateFileW(filename, access, FILE_SHARE_READ, 0, mode, FILE_ATTRIBUTE_NORMAL, 0);
    HeapFree(GetProcessHeap(), 0, (LPVOID)filename);
    return f;
}

intern inline void
file_close(File f) {
    CloseHandle(f);
}

intern u64
file_get_size(File f) {
    LARGE_INTEGER size = {0};
    if (!GetFileSizeEx(f, &size))
        return 0;
    return (u64)size.QuadPart;
}

intern bool
file_write(File f, string s) {
    DWORD written;
    BOOL result = WriteFile(f, s.data, s.size, &written, 0);
    return result && (written == s.size);
}

intern inline bool
file_read(File f, char* dest, u64 bytes_to_read, u64 actually_read) {
    return (bool)ReadFile(f, dest, (DWORD)bytes_to_read, (LPDWORD)actually_read, 0);
}

intern inline bool
file_read_to_string(File f, string* dest) {
    u64 bytes_to_read = file_get_size(f);

    dest->size = bytes_to_read + 1;
    dest->data = (char*)malloc(sizeof(u8) * dest->size);
    dest->data[bytes_to_read] = '\0';

    u64 actually_read = 0;
    if (!file_read(f, dest->data, dest->size, actually_read))
        return false;
    return true;
}

#else
#error IO is currently no implemented for your OS
#endif

#endif // __IO_H_