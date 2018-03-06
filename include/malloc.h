/*
** EPITECH PROJECT, 2021
** PSU_2017_malloc
** File description:
** Created by yohan,
*/

#ifndef PSU_2017_MALLOC_MALLOC_H
#define PSU_2017_MALLOC_MALLOC_H

#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

/*
 * Structure for block's memory info
 */
struct  __attribute__((__packed__)) memory_block_s {
	size_t size;
	struct memory_block_s *next;
	struct memory_block_s *prev;
	bool is_free;
};
typedef struct memory_block_s *memory_block_t;

/*
 * Global variables
 */
extern void *heap_g;
extern const void *head_g;
extern memory_block_t tail_g;
extern pthread_mutex_t thread_g;

/*
 * Aligning pointers
 */
#define align(x) ((x + (sizeof(void*) - 1)) & -sizeof(void*))

/*
 * Define for malloc, free, realloc...
 */
void *malloc(size_t size);
void free(void*);
void *realloc(void*, size_t);
void *calloc(size_t, size_t);

/*
 * Define tools for memory's gesture
 */
memory_block_t available_block(const size_t);
memory_block_t add_mapped_region(const size_t);
void cut_block(memory_block_t, const size_t);
memory_block_t get_block(void*);
void show_alloc_mem();
void merge(memory_block_t);

/*
 * Basic tools
 */
void my_putstr(const char*);
void my_put_nbr(int);
void my_put_nbr_base(size_t, const char*);
//memory_block_t merge(memory_block_t);

/*
 * Define MACRO
 */
#define BIG_SIZE 32000
#define PAGE_SIZE getpagesize()
#define META_DATA_SIZE 4 * sizeof(void*) // = sizeof(struct memory_block_s)
#define HEXA_B "0123456789abcdef"

#endif /* !PSU_2017_MALLOC_MALLOC_H */