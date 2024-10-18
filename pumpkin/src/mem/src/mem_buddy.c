#include <mem_buddy.h>

char memory_pool[MAX_MEM];

struct Block* free_list = 0;

ulong next_power_of_two(ulong n){
    ulong power = MIN_MEM;
    while(power < n){
        power *= 2;
    }
    return power;
}

void buddy_init(){
    struct Block* initial_block = (struct Block*)memory_pool;
    initial_block->size = MAX_MEM;
    initial_block->next = 0;

    free_list = initial_block;
}

void split_block(struct Block* block, ulong size_needed){
    while(block->size > size_needed){
        ulong half_size = block->size / 2;

        struct Block* buddy = (struct Block*)((char*)block + half_size);
        buddy->size = half_size;
        buddy->next = free_list;
        free_list = buddy;

        block->size = half_size;
    }
}

void* buddy_alloc(ulong size){
    ulong block_size = next_power_of_two(size + sizeof(struct Block));

    struct Block** current = &free_list;
    struct Block* prev = 0;

    while (*current != 0 && (*current)->size < block_size){
        prev = *current;
        current = &(*current)->next;
    }

    if(*current == 0){
        return 0;
    }

    struct Block* block = *current;
    *current = block->next;

    split_block(block, block_size);

    return (void*)((char*)block + sizeof(struct Block));
}

struct Block* find_buddy(struct Block* block){
    ulong buddy_address = ((ulong)((char*)block - memory_pool)) ^ block->size;
    return (struct Block*)(memory_pool + buddy_address);
}

void buddy_free(void* ptr){
    struct Block* block = (struct Block*)((char*)ptr - sizeof(struct Block));

    while (block->size < MAX_MEM) 
    {
        struct Block* buddy = find_buddy(block);

        struct Block** current = &free_list;
        struct Block* prev = 0;

        while (*current != 0 && *current != buddy){
            prev = *current;
            current = &(*current)->next;
        }
        
        if (*current == buddy && buddy->size == block ->size){

            if(prev){
                prev->next = buddy->next;
            } else{
                free_list = buddy->next;
            }

            if(buddy< block){
                block = buddy;
            }

            block->size *= 2;
        } else{
            break;
        }
    } 

    block->next = free_list;
    free_list = block;
}