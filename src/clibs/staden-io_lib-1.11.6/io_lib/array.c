/*
 * Copyright (c) Medical Research Council 1994. All rights reserved.
 *
 * Permission to use, copy, modify and distribute this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * this copyright and notice appears in all copies.
 *
 * This file was written by James Bonfield, Simon Dear, Rodger Staden,
 * as part of the Staden Package at the MRC Laboratory of Molecular
 * Biology, Hills Road, Cambridge, CB2 2QH, United Kingdom.
 *
 * MRC disclaims all warranties with regard to this software.
 */

/*
 * File: array.c
 * Version:
 *
 * Description:
 *
 * Created:
 * Updated:
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <limits.h>    /* IMPORT: INT_MAX */

#include "io_lib/array.h"
#include "io_lib/xalloc.h"


/*
 * For error reporting
 */
int ArrayError = 0;


char *ArrayErrorString(int err)
{
    switch(err) {
    case ARRAY_NO_ERROR:          return "No error";
    case ARRAY_FULL:     	  return "Array full";
    case ARRAY_INVALID_ARGUMENTS: return "Invalid arguments";
    case ARRAY_OUT_OF_MEMORY:     return "Out of memory";
    default:			  return "Unknown error";
    }
}



Array ArrayCreate(size_t size, int dim)
/*
 * create a new array
 */
{
    Array a;
    
    if ( (a = (Array) xmalloc(sizeof(ArrayStruct)) ) == NULL ) {
	ArrayError = ARRAY_OUT_OF_MEMORY;
    } else {
	a->size = size;
	a->dim = dim?dim:1;
	a->max = 0;
	if ( (a->base = (void *)xmalloc(a->size * a->dim)) == NULL ) {
	    ArrayError = ARRAY_OUT_OF_MEMORY;
	    xfree(a);
	    a = NULL;
	}
    }
    
    return a;
    
}



int ArrayExtend(Array a, int dim)
/*
 * extend array
 */
{
    void *newbase;

    if (a == NULL) return ArrayError = ARRAY_INVALID_ARGUMENTS;
    if (dim < a->dim) return ArrayError = ARRAY_NO_ERROR;

    while (dim >= a->dim) {
	if (2 * a->dim >= INT_MAX)
	    return ArrayError = ARRAY_FULL;
	else
	    a->dim *= 2;
    }

    if ( (newbase = (void *)xrealloc(a->base, a->size * a->dim)) == NULL )
	return ArrayError = ARRAY_OUT_OF_MEMORY;
    else
	a->base = newbase;

    return ArrayError = ARRAY_NO_ERROR;
}




void *ArrayRef(Array a, int i)
{
    if (a==NULL) {
	ArrayError = ARRAY_INVALID_ARGUMENTS;
	return NULL;
    }

    if (i >= a->max) {
	if (i >= a->dim) {
	    if (ArrayExtend(a,i+1)) {
		/* ArrayExtend sets ArrayError */
		return NULL;
	    }
	}
	a->max = i+1;
    }

    return (void *) arrp(char,a,i*a->size);
}



int ArrayDestroy(Array a)
/*
 * destroy array
 */
{
    if (a==NULL) return ArrayError = ARRAY_INVALID_ARGUMENTS;
    
    if (a->base != NULL) xfree(a->base);
    a->base= NULL;
    xfree(a);

    return ArrayError = ARRAY_NO_ERROR;
    
    
}


