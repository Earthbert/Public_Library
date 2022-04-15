#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include "Hashtable.h"
#include "utils.h"

// Messages
#define BOOK_NOT_FOUND printf("The book is not in the library.\n");
#define DEF_NOT_FOUND printf("The definition is not in the book.\n");

#define MAX_B_NAME_SIZE 60
#define MAX_VAL_SIZE 30
#define MAX_KEY_SIZE 30

// Used at reading book name
#define SCANF_WHOLE(str)									\
	if (scanf(" \42%[^\42]\42", str) == 0) {					\
			scanf("%s", str);								\
	}														\

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
free_book_struct(void *book);

void
add_book(hashtable_t *lib);

void
get_book(hashtable_t *lib);

void
rmv_book(hashtable_t *lib);

void
add_def(hashtable_t *lib);

void
get_def(hashtable_t *lib);

void
rmv_def(hashtable_t *lib);

int
compare_books(const void *data_1, const void *data_2);

void
print_b_info(info_t *data);

#endif  // _LIBRARY_H_
