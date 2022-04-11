/*
 * Hashtable.c
 * Alexandru-Cosmin Mihai
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "LinkedList.h"
#include "Hashtable.h"

#define MAX_BUCKET_SIZE 64

int
compare_function_ints(void *a, void *b)
{
	int int_a = *((int *)a);
	int int_b = *((int *)b);

	if (int_a == int_b) {
		return 0;
	} else if (int_a < int_b) {
		return -1;
	} else {
		return 1;
	}
}

int
compare_function_strings(void *a, void *b)
{
	char *str_a = (char *)a;
	char *str_b = (char *)b;

	return strcmp(str_a, str_b);
}

/*
 * Functii de hashing:
 */
unsigned int
hash_function_int(void *a)
{
	/*
	 * Credits: https://stackoverflow.com/a/12996028/7883884
	 */
	unsigned int uint_a = *((unsigned int *)a);

	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = ((uint_a >> 16u) ^ uint_a) * 0x45d9f3b;
	uint_a = (uint_a >> 16u) ^ uint_a;
	return uint_a;
}

unsigned int
hash_function_string(void *a)
{
	/*
	 * Credits: http://www.cse.yorku.ca/~oz/hash.html
	 */
	unsigned char *puchar_a = (unsigned char*) a;
	unsigned long hash = 5381;
	int c;

	while ((c = *puchar_a++))
		hash = ((hash << 5u) + hash) + c; /* hash * 33 + c */

	return hash;
}

hashtable_t *
ht_create(unsigned int hmax, unsigned int (*hash_function)(void*),
		int (*compare_function)(void*, void*))
{
	hashtable_t *ht;
	ht = calloc(1, sizeof(hashtable_t));
	ht->buckets = calloc(hmax, sizeof(linked_list_t *));
	for (unsigned int i = 0; i < hmax; i++) {
		ht->buckets[i] = ll_create(sizeof(info));
	}
	ht->hmax = hmax;
	ht->hash_function = hash_function;
	ht->compare_function = compare_function;
	return ht;
}

void
ht_put(hashtable_t *ht, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	if (ht == NULL)
		return;

	unsigned int index = ht->hash_function(key) % ht->hmax;

	void *old_value = ht_get(ht, key);
	if (old_value != NULL) {
		memcpy(old_value, value, value_size);
	} else {
		info set;
		set.key = calloc(1, key_size);
		memcpy(set.key, key, key_size);
		set.value = calloc(1, value_size);
		memcpy(set.value, value, value_size);
		ll_add_nth_node(ht->buckets[index], ht->buckets[index]->size, &set);
		ht->buckets[index]->size++;
	}
	ht->size++;
}

void *
ht_get(hashtable_t *ht, void *key)
{
	if (ht == NULL)
		return NULL;
	
	unsigned int index = ht->hash_function(key) % ht->hmax;

	ll_node_t *node = ht->buckets[index]->head;

	while (node)
	{
		if(ht->compare_function(key, ((info *)node->data)->key) == 0)
			return ((info *)node->data)->value;
		node = node->next;
	}

	return NULL;
}

int
ht_has_key(hashtable_t *ht, void *key)
{
	if (ht == NULL)
		return 0;

	unsigned int index = ht->hash_function(key) % ht->hmax;
	
	ll_node_t *node = ht->buckets[index]->head;
	while (node)
	{
		if(ht->compare_function(key, ((info *)node->data)->key) == 0)
			return 1;
		node = node->next;
	}
	
	return 0;
}

void
ht_remove_entry(hashtable_t *ht, void *key)
{
	if (ht == NULL)
		return;

	unsigned int index = ht->hash_function(key) % ht->hmax;
	
	ll_node_t *node = ht->buckets[index]->head;
	unsigned int n = 0;
	while (node)
	{
		if(ht->compare_function(key, ((info *)node->data)->key) == 0) {
			ll_node_t *node = ll_remove_nth_node(ht->buckets[index], n);
			info *data = (info *)node->data;
			free(data->key);
			free(data->value);
			free(data);
			free(node);
			ht->buckets[index]->size--;
			ht->size--;
			return;
		}
		n++;
		node = node->next;
	}
}

// Frees memory of a hashtable
// Doesn't free the hashtable itself
void
ht_free(hashtable_t *ht)
{
	if (ht == NULL)
		return;
	for (unsigned int i = 0; i < ht->hmax; i++) {
		ll_free(ht->buckets[i]);
	}
	free(ht->buckets);
}

void
resize_ht(hashtable_t *ht, double load_factor) {
	if (ht == NULL)
		return;
	if ((ht->size / ht->hmax) < load_factor)
		return;
	
	linked_list_t **new_buckets = calloc(ht->hmax * 2, sizeof(linked_list_t *));
	for (unsigned int i = 0; i < ht->hmax * 2; i++)
		new_buckets[i] = ll_create(sizeof(info));
	
	for (unsigned int i = 0; i < ht->hmax; i++) {
		ll_node_t *node = ht->buckets[i]->head;
		while (node) {
			info *data = (info *)node->data;
			unsigned int index = ht->hash_function(data->key) % (ht->hmax * 2);
			ll_add_nth_node(new_buckets[index], new_buckets[index]->size, data);
		}
	}
	ht_free(ht);
	ht->buckets = new_buckets;
}
