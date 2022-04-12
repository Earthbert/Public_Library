#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Hashtable.h"

// Error messages
#define BOOK_NOT_FOUND printf("The book is not in the library.\n");
#define DEF_NOT_FOUND printf("The definition is not in the book.\n");

// Stored data about a book
// The name will be stored as the key in the lib hashtable
typedef struct book_t book_t;
struct book_t{
	// Hashtable of definitions
	hashtable_t *defs;
	// Rating of the book
	double rating;
	// Nr of purchases
	unsigned int purchases;

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

#endif  // _LIBRARY_H_
