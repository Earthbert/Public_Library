#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "library.h"

void
free_book_struct(void *book)
{
	ht_free(((book_t *)book)->defs, &free);
	free(book);
}

void
add_book(hashtable_t *lib, char *book_name, unsigned int nr_defs)
{
	book_t b_data;
	b_data.defs = ht_create(HTMAX, &hash_function_string, &compare_function_strings);
	b_data.purchases = 0;
	b_data.rating = 0;

	char def_key[20];
	char def_value[20];
	for (unsigned int i = 0; i < nr_defs; i++) {
		scanf("%s %s", def_key, def_value);
		ht_put(b_data.defs, def_key, strlen(def_key) + 1, def_value, strlen(def_value) + 1, LOAD_F);
	}

	ht_put(lib, book_name, strlen(book_name) + 1, &b_data, sizeof(b_data), LOAD_F);
}

void
get_book(hashtable_t *lib, char *book_name)
{
	book_t *book = ht_get(lib, book_name);
	if (!book) {
		BOOK_NOT_FOUND
		return;
	}

	printf("Name:%s Rating:%s Purchase:%s\n", book_name, book->rating, book->purchases);
}

void
rmv_book(hashtable_t *lib, char *book_name)
{
	int ret_val = ht_remove_entry(lib, book_name, &free_book_struct);

	if (!ret_val) {
		BOOK_NOT_FOUND
	}
}

void
add_def(hashtable_t *lib, char *book_name, char *def_key, char *def_value)
{
	book_t *book = ht_get(lib, book_name);
	if (!book) {
		BOOK_NOT_FOUND
		return;
	}

	ht_put(lib, def_key, strlen(def_key) + 1, def_value, strlen(def_value) + 1, LOAD_F);
}

void
get_def(hashtable_t *lib, char *book_name, char *def_key)
{
	book_t *book = ht_get(lib, book_name);
	if (!book) {
		BOOK_NOT_FOUND
		return;
	}

	char *def = ht_get(book->defs, def_key);
	if (!def) {
		DEF_NOT_FOUND
		return;
	}

	printf("%s\n", def);
}

void
rmv_def(hashtable_t *lib, char *book_name, char *def_key)
{
	book_t *book = ht_get(lib, book_name);
	if (!book) {
		BOOK_NOT_FOUND
		return;
	}

	int ret_val = ht_remove_entry(book->defs, def_key, &free);

	if (!ret_val) {
		DEF_NOT_FOUND
	}
}
