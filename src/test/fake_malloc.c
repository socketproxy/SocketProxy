/***
 * socketproxy/src/test/fake_malloc.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <stdio.h>
    
void *
malloc( size_t i)
{
    printf ("Hello from malloc");
    return realloc(NULL, i);
}

