/**
 * Useful structures/macros
 * 
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define ALLOC_ERR "Allocation Error"

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {												\
		if (assertion) {								\
			fprintf(stderr, "(%s, %d): ",				\
					__FILE__, __LINE__);				\
			perror(call_description);					\
			exit(errno);				        		\
		}												\
	} while (0)

char *
strdup(char *s)
{
	int len = strlen(s) + 1;
	char *new_s = calloc(len, sizeof(char));
	DIE(!new_s, ALLOC_ERR);
	memcpy(new_s, s, len);
	return new_s;
}

#endif /* __UTILS_H_ */
