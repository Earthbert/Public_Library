#ifndef _USER_OP_H_
#define _USER_OP_H_

#include "Hashtable.h"
#include "utils.h"

// Messages
#define ALREADY_REG printf("User is already registered\n");
#define NOT_REG printf("You are not registered yet.\n");
#define BANNED printf("You are banned from this library.\n");
#define BORROWED printf("The book is borrowed.\n");
#define ALREADY_BWD printf("You have already borrowed a book.\n");
#define USER_BANNED(usr) printf("The user %s has been banned.\n", usr);
#define NOT_BWD_BOOK printf("You didn't borrow this book.");

// Holds information about user
// The name of the user will be the key in the users hashtable
typedef struct user_data_t user_data_t;
struct user_data_t
{
	// The score of an user
	int score;
	// Is 1 is user is banned, 0 otherwise
	int is_banned;
	// Name of the barrowed book
	char *b_book;
	// Days to return a book, if user doesn't have a book borrowed days is -1
	int days;
};

void
add_user(hashtable_t *usr_table, char *name);

void
borrow_book(hashtable_t *usr_table, hashtable_t *lib , char *name, char *b_name, int days);

void
return_book(hashtable_t *usr_table, hashtable_t *lib, char *name, char *b_name, int days, double rating);

void
lost_book(hashtable_t *usr_table, hashtable_t *lib, char *name, char *b_name);

int
compare_users(info_t *usr_1, info_t *usr_2);

#endif  // _USER_OP_H_