#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "user_op.h"
#include "library_op.h"

#define MAX_CMD_SIZE 10

int main()
{
	hashtable_t *usr_table = ht_create(HTMAX, &hash_function_string, &compare_function_strings, &free_user_struct);
	hashtable_t *lib = ht_create(HTMAX, &hash_function_string, &compare_function_strings, &free_book_struct);

	char command[MAX_CMD_SIZE];

	while (1) {
		scanf("%s", command);
		if (!strcmp(command, "ADD_BOOK")) {
			add_book(lib);
			continue;
		}
		if (!strcmp(command, "GET_BOOK")) {
			get_book(lib);
			continue;
		}
		if (!strcmp(command, "RMV_BOOK")) {
			rmv_book(lib);
			continue;
		}
		if (!strcmp(command, "ADD_DEF")) {
			add_def(lib);
			continue;
		}
		if (!strcmp(command, "GET_DEF")) {
			get_def(lib);
			continue;
		}
		if (!strcmp(command, "RMV_DEF")) {
			rmv_def(lib);
			continue;
		}
		if (!strcmp(command, "ADD_USER")) {
			add_user(usr_table);
			continue;
		}
		if (!strcmp(command, "BORROW")) {
			borrow_book(usr_table, lib);
			continue;
		}
		if (!strcmp(command, "RETURN")) {
			return_book(usr_table, lib);
			continue;
		}
		if (!strcmp(command, "LOST")) {
			lost_book(usr_table, lib);
			continue;
		}
		if (!strcmp(command, "EXIT")) {
			print_ranking(usr_table, lib);
			break;
		}
		printf("Invalid command\n");
	}

	ht_free(usr_table);
	ht_free(lib);
	return 0;
}