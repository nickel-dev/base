#ifndef __STRING_H_
#define __STRING_H_

#define str(x) ((string){x, cstr_length(x)})

intern u64
cstr_length(u8* s) {
    u8* p = s;
    while (*s)
        ++s;
    return (u64)(p - s);
}

#endif // __STRING_H_