#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "LinkedList.h"

#define HTMAX 10
#define LOAD_F 1.0

#define HT_U "Hashtable uninitialized"

typedef struct info_t info_t;
struct info_t
{
	void *key;
	void *value;
};


typedef struct hashtable_t hashtable_t;
struct hashtable_t
{
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax;
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
};

//----Hashtable functions

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*));

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size, double load_factor);

void *
ht_get(hashtable_t *ht, void *key);

int
ht_has_key(hashtable_t *ht, void *key);

int
ht_remove_entry(hashtable_t *ht, void *key, void (*free_value_f)(void *));

void
ht_free(hashtable_t *ht, void (*free_value_f)(void *));

void
resize_ht(hashtable_t *ht, double load_factor);

info_t *
ht_sort(hashtable_t *ht, int (*compare_func)(const void *,const void *));

void
ht_print(hashtable_t *ht, void (*print_data)(info_t *));

//----Compare key functions
int
compare_function_ints(void *a, void *b);

int
compare_function_strings(void *a, void *b);

//----Hashing functions

unsigned int
hash_function_int(void *a);

unsigned int
hash_function_string(void *a);

#endif  // __HASHTABLE_H
