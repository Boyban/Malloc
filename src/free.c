/*
** EPITECH PROJECT, 2021
** Malloc_2
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
 * Function that get the header of an memory area/region
 *
 * @address is a pointer to the first address of memory area/region
 *
 * Creating a "char*", in cause we want to use bytes precision
 * Subtract the header size at the address to be in header first pointer
 * @return a pointer to the header of @address
 */
memory_block_t get_block(void *address)
{
	char *tmp = address;

	tmp -= META_DATA_SIZE;
	return (address = tmp);
}

/*
 * Function that checks if address exists
 *
 * @address is a pointer to address to check
 *
 * Checking the state of address and look in interval of @head_g and break
 * @return 0 in case of error or 1 if address exist
 */
static int check_address(const void *address)
{
	if (address && (address >= head_g && address < sbrk(0)))
		return (1);
	return (0);
}

/*
 * Function that remove an element in list and decrease the heap
 *
 * @block is a pointer of the element to remove
 * @prev is a checker to know if the previous element is free and can be remove
 *
 * Checking if previous is a element free and is the previous address in heap
 * Placing the next of previous block at the current block next
 * In case of there is not previous block that signify the block is the first
 * of list and we have to move the heap_g at the next block
 * Perform the same operation for the next conversely with the previous
 * In case of there is not next block that signify the block is the last element
 * if list and we move the @tail_g to previous block of current
 *
 * sbrk() with negative perform an operation that deallocate memory area in heap
 * Removing the memory area about the block with header size
 * If the previous has to be remove we call recursively the function
 */
static void remove_address(memory_block_t block)
{
	memory_block_t prev = NULL;

	if (block->prev && block->prev->is_free &&
		(char*)block->prev + block->prev->size + META_DATA_SIZE ==
			(char*)block)
			prev = block->prev;
	if (block->prev)
		block->prev->next = block->next;
	else
		heap_g = block->next;
	if (block->next)
		block->next->prev = block->prev;
	else
		tail_g = block->prev;
	sbrk(-(block->size + META_DATA_SIZE));
	if (prev)
		remove_address(prev);
}

/*
 * Function that makes a block becomes the last element in list
 *
 * @block is the current to move
 *
 * Checking if the block is already the last in this case we exit the function
 * Like remove address, perform the subtract of the block in the list
 * After that, the last element of list take the block at the next
 * Block take his prev (previous pointer) on @tail_g
 * Moving @tail_g on current @block
 */
static void move_address(memory_block_t block)
{
	if (!block->next)
		return;
	if (block->prev)
		block->prev->next = block->next;
	else
		heap_g = block->next;
	if (block->next) {
		block->next->prev = block->prev;
		block->prev = tail_g;
		if (tail_g)
			tail_g->next = block;
		tail_g = block;
	}
	block->next = NULL;
}

/*
 * Free re-implement of the original free in concordance with re-implementation
 * of malloc
 *
 * @address is the current address to free
 *
 * Checking if address exist in list in case of not the block is not modify
 * Locking @thread_g to protect the memory
 * Getting block and checking if the block is the last address in Heap
 * In case of he is we can remove it
 * Else we move it in the end of list
 * If the block prev is free and it's address is the precedent of current
 * @address in Heap we can us
 * Unlocking Thread protection
 */
void free(void *address)
{
	memory_block_t block;

	if (!check_address(address))
		return;
	pthread_mutex_lock(&thread_g);
	block = get_block(address);
	block->is_free = true;
	if ((char*)block + block->size + META_DATA_SIZE == sbrk(0)) {
		remove_address(block);
		pthread_mutex_unlock(&thread_g);
		return;
	}
	move_address(block);
	if (block->prev && ((char*)block + block->prev->size + META_DATA_SIZE
		== (char*)block))
		merge(block->prev);
	pthread_mutex_unlock(&thread_g);
}
