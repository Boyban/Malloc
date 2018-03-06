/*
** EPITECH PROJECT, 2021
** Malloc_2
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
* Global variable for malloc implementation
*
* @heap_g is all time a pointer to address of first element in list of
* memory address
*
* @head_g is all time a pointer to the first address in the Heap
 * Do not confound heap_g and head_g can be different address because of free
 *
 * @tail_g is a pointer who can be move at all operations performs
 * He point to the address of the last element in list of memory address
 *
 * @thread_g is a thread initializer who permit to protect any memory area
 * in threaded program
 */
void *heap_g = NULL;
const void *head_g;
memory_block_t tail_g = NULL;
pthread_mutex_t thread_g = PTHREAD_MUTEX_INITIALIZER;

/*
 * Malloc is re-implementation of original malloc
 *
 * memory_block_t represent header of an allocated area (cf. malloc.h)
 * We align the size with an aligning function
 * Aligning size is the right way to return an aligning pointer
 * Pointer have not to be align with this method because the header size is
 * already align
 *
 * pthread_mutex_lock & *unlock method is a way to block use of same memory area
 * when malloc is called in multi-threading function
 *
 * On start malloc added memory region
 * When a program perform many request malloc check if already free block exist
 * Else he added a new memory region suitable by program request
 *
 * @size is area size request by program (cf. man malloc)
 * @return The first address after header of memory area
 */
void *malloc(size_t size)
{
	memory_block_t block;
	size_t aligned_size = align(size);

	pthread_mutex_lock(&thread_g);
	if (!heap_g) {
		head_g = sbrk(0);
		block = add_mapped_region(aligned_size);
		heap_g = block;
	} else if (aligned_size < BIG_SIZE) {
		block = available_block(aligned_size);
		if (block) {
			block->size - aligned_size >
			META_DATA_SIZE + sizeof(void*) ?
			cut_block(block, aligned_size) : block;
			block->is_free = false;
		} else
			block = add_mapped_region(aligned_size);
	} else
		block = add_mapped_region(aligned_size);
	pthread_mutex_unlock(&thread_g);
	return (block ? (char*)block + META_DATA_SIZE : NULL);
}
