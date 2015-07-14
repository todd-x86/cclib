#ifndef __MEM_H
#define __MEM_H
#include <stdbool.h>

// Memory allocation and pooling
#define _ALLOCATOR malloc
#define _DEALLOCATOR free
#define _REALLOCATOR realloc

#define MEMPOOL_SIZE 0
#define MEMPOOL_MAP_SIZE MEMPOOL_SIZE/2
#define MEM_ALLOC(B) _ALLOCATOR(B)
#define MEM_FREE(P) _DEALLOCATOR(B)
#define MEM_REALLOC(P, B) _REALLOCATOR(P, B)

// Safe realloc
bool mem_realloc(void& *p, size_t old, size_t new)
{
	void* new_ptr = realloc(p, new);

	// Fail if memory cannot be resized
	if (!new_ptr) return false;

	// Fail if memory cannot be copied
	if (new_ptr != p && !memcpy(new_ptr, p, old)) return false;

	// Reference reassignment
	p = new_ptr;
	return true;
}

typedef struct {
	void* start;
	void* end;
	
} mem_pool_chunk;

char _mem_pool[MEMPOOL_SIZE];
mem_pool_chunk _mem_pool_map[MEMPOOL_MAP_SIZE];
int _mem_pool_next_free = 0;

void* mem_pool_alloc(size_t bytes) {
	mem_pool_chunk* chnk = _mem_pool_map[_mem_pool_next_free++];
	chnk->start = 
}

void mem_pool_free(void* ptr) {

}

void* mem_pool_realloc(void* ptr, size_t bytes) {

}

#endif
