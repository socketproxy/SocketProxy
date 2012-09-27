#include <stdlib.h>
#include <stdio.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <string.h>

/* 
 * Imagine a program that receives a piece of sensitive data
 * such as a passphrase, encrypts the passphrase with a call
 * to crypt(3), and stores it some place. This is a mock-up
 * of that program.
 */


/***
 * recv_secret -- get a secret from the secret place
 *
 * @param: none
 * @return: a dynamically allocated string containing the secret on success,
 *		or NULL on failure.
 *
 */
char *
recv_secret ( void ) {

	size_t len;
	char *secret = "Rosebud? A sled.";
	char *dsecret;


	len = ( ( strlen ( secret ) + 1 ) * sizeof ( char ) );

	if ( (dsecret = malloc( len ) ) == NULL ){
		return NULL;
	}

	bzero ( dsecret, len );

	strncpy ( dsecret, secret, len - 1 );

	return dsecret;
} /* end of recv_secret() */



/***
 * store_encrypted_secret -- stores the encrypted secret securely
 * @param: encrypted secret
 * @return: 1 on success, 0 on failure
 *
 */
int 
store_encrypted_secret( char *esecret ) {

	return 1; /* HAHAHAHAHAHA */

} /* end of store_encrypted_secret() */



int
main (int argc, char **argv)
{

	char *secret;
	char *encrypted_secret;
	unsigned int len;
	const char *salt = "/."; /* Slashdot! */

	/* receive the secret */
	if ( ( secret = recv_secret() ) == NULL ) {
		/* XXX die with error */
		exit ( 1 );
	}

	/* encrypt the secret */
	if ( (encrypted_secret = crypt( secret, salt )) == NULL ) {
		/* XXX die with error */
		exit ( 1 );
	}

	/* write store_encrypted_secret() */
	if ( ! store_encrypted_secret( encrypted_secret ) ) {
		/* XXX die with error */
		exit ( 1 );
	}

	exit ( 0 ) ;

}
