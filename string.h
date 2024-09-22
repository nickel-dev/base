#ifndef __STRING_H_
#define __STRING_H_

global const string null_string = {0, 0};

intern u64
cstr_length(char* s) {
    char* p = s;
    while (*s)
        ++s;
    return (u64)(p - s);
}

// We take in const char* and convert it, due to C automatically putting in coinst char*
intern inline string
str(const char* s) {
    return (string){(char*)s, cstr_length((char*)s)};
}

intern string
string_alloc(Arena arena, u64 size) {
    string s;
    s.data = (char*)alloc(arena, sizeof(char) * size);
    s.size = size;
    return s;
}

intern string
string_trim(Arena arena, string s, u64 start, u64 end) {
    string result = string_alloc(arena, end - start + 1);
    memcpy((void*)result.data, (void*)((u8*)s.data + start), result.size);
    return result;
}

intern bool
string_compare(string a, string b) {
    if (a.size != b.size)
        return false;
    
    while (*a.data) {
        if (*a.data != *b.data)
            return false;
        ++a.data;
        ++b.data;
    }
    return true;
}

#endif // __STRING_H_