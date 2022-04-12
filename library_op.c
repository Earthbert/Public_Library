#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library_op.h"

// Used at removing entries from lib hashtable
void
free_book_struct(void *book)
{
	ht_free(((book_info_t *)book)->defs, &free);
	free(book);
}

// Addes book in library
// Reads definitions from stdin
void
add_book(hashtable_t *lib, char *book_name, unsigned int nr_defs)
{
	book_info_t b_data;
	b_data.defs = ht_create(HTMAX, &hash_function_string, &compare_function_strings);
	b_data.purchases = 0;
	b_data.rating = 0;
	b_data.barrowed = 0;

	char def_key[20];
	char def_value[20];
	for (unsigned int i = 0; i < nr_defs; i++) {
		scanf("%s %s", def_key, def_value);
		ht_put(b_data.defs, def_key, strlen(def_key) + 1, def_value, strlen(def_value) + 1, LOAD_F);
	}

	ht_put(lib, book_name, strlen(book_name) + 1, &b_data, sizeof(b_data), LOAD_F);
}

// Prints information about a book
void
get_book(hashtable_t *lib, char *book_name)
{
	book_info_t *b_data = ht_get(lib, book_name);
	if (!b_data) {
		BOOK_NOT_FOUND
		return;
	}

	printf("Name:%s Rating:%s Purchase:%s\n", book_name, b_data->rating, b_data->purchases);
}

// Removes a book 
void
rmv_book(hashtable_t *lib, char *book_name)
{
	int ret_val = ht_remove_entry(lib, book_name, &free_book_struct);

	if (!ret_val) {
		BOOK_NOT_FOUND
	}
}

// Adds a new definion in a book
void
add_def(hashtable_t *lib, char *book_name, char *def_key, char *def_value)
{
	book_info_t *b_data = ht_get(lib, book_name);
	if (!b_data) {
		BOOK_NOT_FOUND
		return;
	}

	ht_put(lib, def_key, strlen(def_key) + 1, def_value, strlen(def_value) + 1, LOAD_F);
}

// Prints a requested definition
void
get_def(hashtable_t *lib, char *book_name, char *def_key)
{
	book_info_t *b_data = ht_get(lib, book_name);
	if (!b_data) {
		BOOK_NOT_FOUND
		return;
	}

	char *def = ht_get(b_data->defs, def_key);
	if (!def) {
		DEF_NOT_FOUND
		return;
	}

	printf("%s\n", def);
}

// Removes definitions from a given book
void
rmv_def(hashtable_t *lib, char *book_name, char *def_key)
{
	book_info_t *b_data = ht_get(lib, book_name);
	if (!b_data) {
		BOOK_NOT_FOUND
		return;
	}

	int ret_val = ht_remove_entry(b_data->defs, def_key, &free);

	if (!ret_val) {
		DEF_NOT_FOUND
	}
}

// Compares two books by rating, nr of purchases and name in order.
int
compare_books(info_t *data_1, info_t *data_2) {
	book_info_t *b_data_1 = (book_info_t *)data_1->value;
	book_info_t *b_data_2 = (book_info_t *)data_2->value;

	if (b_data_1->rating > b_data_2->rating) {
		return 1;
	} else if (b_data_1->rating < b_data_2->rating) {
		return -1;
	}

	if (b_data_1->purchases != b_data_2->purchases) {
		return b_data_1->purchases - b_data_2->purchases;
	}

	char *name_1 = data_1->key;
	char *name_2 = data_2->key;

	return strcmp(name_1, name_2);
}
