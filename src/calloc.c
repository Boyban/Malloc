/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
 * Function that allocate an array of nmemb with size
 *
 * @nmemb is the sizeof() of array element
 * @size is the size of array
 * @new_block is a pointer to the address call by malloc()
 *
 * We checking malloc() success, and setting all element of array at 0
 * @return the new block with requested size
 */
void *calloc(size_t nmemb, size_t size)
{
	void *new_block = malloc(nmemb * size);

	if (new_block)
		memset(new_block, 0, align(nmemb * size));
	return (new_block);
}