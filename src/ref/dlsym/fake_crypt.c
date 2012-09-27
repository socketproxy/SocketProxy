#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include <unistd.h>


/***
 * This file implements a wrapper for crypt(3) which prints out
 * the parameters passed in and calls the original crypt(3) with
 * dlsym.
 */

/* This is the fake crypt function. It makes a call to the real crypt(3), 
 * but before it does that it prints out the secret key and the salt.
 */
char *
crypt ( const char *key, const char *salt ) 
{

	/* A function pointer used to hold a reference to the real
	 * crypt(3) function. Note that this is a static pointer.
	 */
	static void* (*real_crypt)(const char *, const char *) = NULL;


	/* Setting the static function pointer. */
	if ( !real_crypt ) {

		/* dlsym is used to get a reference to a dynamically linked
		 * symbol, such as a function in a dynamically linked library.
		 * It takes in two parameters, a "handle" to a dynamically 
		 * linked library from dlopen(2), and the symbol to be linked. 
		 * It returns a pointer to that symbol, or null on error.
		 *
		 * How do you get the handle? I'm not sure, but RTLD_NEXT
		 * is a special pseudo-handle to next library that exports
		 * the symbol you want. Easy-peasy.
		 */

		real_crypt = dlsym(RTLD_NEXT, "crypt");
	}

	printf ( "Secret Collect! key: %s salt: %s\n", key, salt );

	return real_crypt( key, salt );
}
