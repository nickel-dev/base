// Memory is implemented on an OS basis
#ifndef __MEMORY_H_
#define __MEMORY_H_

intern inline void* alloc(Arena a, u64 size);

intern Arena new_arena(u64 size);
intern void arena_free(Arena* a);
intern inline void arena_clear(Arena* a);

#if OS_WINDOWS

intern inline void*
alloc(Arena a, u64 size) {
    a.offset += size;
    return (void*)((u8*)a.start + a.offset);
}

intern Arena
new_arena(u64 size) {
    Arena a = {0};
    a.size = size;
    a.start = HeapAlloc(GetProcessHeap(), 0, a.size);
    return a;
}

intern void
arena_free(Arena* a) {
    assert(HeapFree(GetProcessHeap(), 0, a->start), "Freeing memory block failed! adress: %p", a->start);
    a->start = NULL;
    a->offset = 0;
    a->size = 0;
}

intern inline void
arena_clear(Arena* a) {
    a->offset = 0;
}

#else
#error Memory is currently no implemented for your OS
#endif

#endif // __MEMORY_H_