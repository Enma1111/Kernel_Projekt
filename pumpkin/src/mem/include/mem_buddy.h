#ifndef MEM_BUDDY_H
#define MEM_BUDDY_H

#include <types.h>

#define MAX_MEM (1 << 30)
#define MIN_MEM (1 << 12)

struct Block{
    ulong size;
    struct Block* next;
};

ulong next_power_of_two(ulong n);
void buddy_init();
void split_block(struct Block* block, ulong size_needed);
void* buddy_alloc(ulong size);
struct Block* find_buddy(struct Block* block);
void buddy_free(void* ptr);


#endif