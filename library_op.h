#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Hashtable.h"

// Messages
#define BOOK_NOT_FOUND printf("The book is not in the library.\n");
#define DEF_NOT_FOUND printf("The definition is not in the book.\n");

// Stored data about a book
// The name will be stored as the key in the lib hashtable
typedef struct book_info_t book_info_t;
struct book_info_t
{
	// Hashtable of definitions
	hashtable_t *defs;
	// Rating of the book
	double rating;
	// Nr of purchases
	unsigned int purchases;
	//  Is 1 if book is barrowed
	__int8_t barrowed;
};

void
add_book(hashtable_t *lib, char *book_name, unsigned int nr_defs);

void
get_book(hashtable_t *lib, char *book_name);

void
rmv_book(hashtable_t *lib, char *book_name);

void
add_def(hashtable_t *lib, char *book_name, char *def_key, char *def_value);

void
get_def(hashtable_t *lib, char *book_name, char *def_key);

void
rmv_def(hashtable_t *lib, char *book_name, char *def_key);

int
compare_books(info_t *data_1, info_t *data_2);

#endif  // _LIBRARY_H_
