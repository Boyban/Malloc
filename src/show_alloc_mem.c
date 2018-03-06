/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by yohan,
*/

#include "malloc.h"

/*
 * Simple write for string
 */
void my_putstr(const char *str)
{
	write(1, str, strlen(str));
}

/*
 * Simple implementation of strlen()
 */
int my_strlen(const char *str)
{
	int i = 0;

	while (str[i])
		++i;
	return (i);
}

/*
 * Function that writes an int in standard output
 */
void my_put_nbr(int nb)
{
	char c;

	if (nb < 0) {
		nb *= -1;
		write(1, "-", 1);
	}
	if (nb < 10) {
		c = nb + '0';
		write(1, &c, 1);
	}
	else {
		c = (nb % 10) + '0';
		my_put_nbr(nb / 10);
		write(1, &c, 1);
	}
}

/*
 * Function that writes an unsigned int (size_t) in requested base in
 * standard output
 */
void my_put_nbr_base(size_t nb, const char *base)
{
	if (nb == 0)
		return;
	my_put_nbr_base(nb / my_strlen(base), base);
	write(1, &base[nb % my_strlen(base)], 1);
}

/*
 * Function that permit memory management and display memory list
 *
 * Displaying the first element of list
 * Displaying address of heap's break
 * Displaying elements of list in while each after each
 * If element if free we don't display it
 * Information display are address of element and it's size in bytes
 */
void show_alloc_mem(void)
{
	memory_block_t block = heap_g;

	my_putstr("Heap: 0x");
	my_put_nbr_base((size_t)heap_g, HEXA_B);
	my_putstr("\n");
	my_putstr("break: 0x");
	my_put_nbr_base((size_t)sbrk(0), HEXA_B);
	my_putstr("\n");
	for (block = block; block != NULL; block = block->next) {
		if (!block->is_free) {
			my_putstr("0x");
			my_put_nbr_base((size_t)block, HEXA_B);
			my_putstr(" - 0x");
			my_put_nbr_base((size_t)(
			(char *)block + META_DATA_SIZE + block->size), HEXA_B);
			my_putstr(" : ");
			my_put_nbr((size_t)block->size);
			my_putstr(" bytes\n");
		}
	}
}