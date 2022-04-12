#ifndef __HASHTABLE_H
#define __HASHTABLE_H

#include "LinkedList.h"

#define HT_U "Hashtable uninitialized"

typedef struct {
	void *key;
	void *value;
} info;


typedef struct {
	linked_list_t **buckets;
	unsigned int size;
	unsigned int hmax;
	unsigned int (*hash_function)(void*);
	int (*compare_function)(void*, void*);
} hashtable_t;

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

void
ht_remove_entry(hashtable_t *ht, void *key);

void
ht_free(hashtable_t *ht, void *free_value_func(void *));

void
resize_ht(hashtable_t *ht, double load_factor);

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
