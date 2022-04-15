// Copyright 2022 Daraban Albert-Timotei
/**
 * Useful structures/macros
 * 
 * https://ocw.cs.pub.ro/courses/so/laboratoare/resurse/die
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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

#endif  // _UTILS_H_
