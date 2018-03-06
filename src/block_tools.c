/*
** EPITECH PROJECT, 2021
** Malloc_2
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
 * Function that merges two blocks
 *
 * @block is the current block that can be merges with his next
 * He takes his size with the next size and header's size
 * merge is only uses by free and signify the end of the list
 * It's why the next is set to NULL
 */
void merge(memory_block_t block)
{
	block->size += META_DATA_SIZE + block->next->size;
	block->next = NULL;
}

/*
 * Function that get a free block with minimum size
 *
 * Block is getting the last element because all free blocks are move to the end
 * Tmp get the first element because we change his prev to block find
 *
 * If block correspond to attempt we move is to the head of list
 *
 * @return if block is a block we return it else we return NULL
 */
memory_block_t available_block(const size_t size)
{
	memory_block_t block = tail_g;
	memory_block_t tmp = heap_g;

	while (block && block->size < size && block->is_free)
		block = block->prev;
	if (block && block->is_free) {
		if (block->prev)
			block->prev->next = block->next;
		if (block->next)
			block->next->prev = block->prev;
		else
			tail_g = block->prev;
		block->next = heap_g;
		block->prev = NULL;
		tmp ? tmp->prev = block : tmp;
		heap_g = block;
	}
	return (block && block->is_free && block->size >= size  ? block : NULL);
}

/*
 * Function that requests a new memory area
 *
 * @block is placed to the break of the Heap to be at the
 * next first address allocated
 * @tmp get the first element of memory list to permit the addition of the new
 * block
 * @ps contain a page size who is defined by getpagesize() function
 * @page correspond to the number of page what we need for allocation
 *
 * sbrk() is a 'syscall' that increase the heap size
 * List managements in "if" condition permit to move the new block at head
 * If the block has a size too largest we cut him before return it
 *
 * @return the new block allocated
 */
memory_block_t add_mapped_region(const size_t size)
{
	memory_block_t block = sbrk(0);
	memory_block_t tmp = heap_g;
	size_t ps = PAGE_SIZE;
	size_t page = ((size / ps) * ps < size) ?
		((size / ps) + 1) * ps : (size /ps) * ps;

	page = (page - META_DATA_SIZE < size) ? page + ps : page;
	if (sbrk(page) == (void*)-1)
		return (NULL);
	block->size = page - META_DATA_SIZE;
	block->next = heap_g;
	block->prev = NULL;
	if (heap_g)
		tmp->prev = block;
	heap_g = block;
	if (block->next == NULL)
		tail_g = block;
	block->is_free = false;
	if (page - size > META_DATA_SIZE + (ps / 4))
		cut_block(block, size);
	return (block);
}

/*
 * Function that cuts a block
 *
 * @block is current block to cut
 * @size is the future size of the block
 *
 * Creating a new block at address after size
 * This new block have the size of the block->size - size
 * He's free and it is placed in the end of list
 * Checking the last element of list to place the next on new block
 * @tail_g is the new block
 */
void cut_block(memory_block_t block, const size_t size)
{
	memory_block_t new_block = (memory_block_t)
		(((char*)block + META_DATA_SIZE) + size);

	new_block->size = block->size - size - META_DATA_SIZE;
	new_block->next = NULL;
	new_block->prev = tail_g;
	new_block->is_free = true;
	if (tail_g)
		tail_g->next = new_block;
	tail_g = new_block;
	block->size = size;
}
