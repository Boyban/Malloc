/*
** EPITECH PROJECT, 2021
** Malloc_2
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
 * Realloc re-implementation of original realloc
 *
 * @ptr is a pointer to the memory area to reallocate
 * @size is the size that block must have
 * @tmp pointer that stocks the new address return by a malloc
 * @block is the current block of element pointed by ptr
 * @aligned_size is the size aligned like for malloc
 *
 * Like a classic realloc in case of ptr is non-initialized or NULL we return
 * a malloc with corresponding size
 * Getting block corresponding to address and checking if it non-free
 * else we return a NULL pointer
 * In realloc man it's write when a program request a realloc with 0 in size
 * it's like a free and return NULL
 *
 * After all checking if memory area is largest than size request we can
 * return it
 * Else we call malloc and copy all data with memcpy(), we call free() with
 * last address
 * @return tmp that corresponding to the new memory area
 */
void *realloc(void *ptr, size_t size)
{
	void *tmp;
	memory_block_t block;
	size_t aligned_size = align(size);

	if (!ptr)
		return (malloc(size));
	block = get_block(ptr);
	if (!block || block->is_free)
		return (NULL);
	if (size == 0) {
		free(ptr);
		return (NULL);
	}
	if (block->size >= aligned_size)
		return (ptr);
	tmp = malloc(size);
	if (tmp) {
		memcpy(tmp, ptr, block->size);
		free(ptr);
	}
	return (tmp);
}