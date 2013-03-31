#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/* The path used as an address for the socket */
#define SOCK_PATH "echo_socket"

/* Size of the send/recv buffer */
#define BUFFSIZE 100

int
main ( void ) {

	/* Socket */
	int s;
	int t, len;
	struct sockaddr_un remote;
	char str[BUFFSIZE];

	if ( (s = socket ( AF_UNIX, SOCK_STREAM, 0 )) == -1 ) {
		perror ( "socket" );
		exit(1);
	}

	printf ( "Trying to connect...\n" );



	/***
	 * Setting up for the call to connect 
	 */

	/* socket family is AF_UNIX for unix domain socket. */
	remote.sun_family = AF_UNIX;

	/* Setting the address path with strncpy */
	strncpy ( remote.sun_path, SOCK_PATH, sizeof(remote.sun_path) );

	/* Socket address length is a necessary parameter to connect
	 * and is calculated like this.
	 */
	len = strlen ( remote.sun_path ) + sizeof(remote.sun_family);

	if ( connect ( s, (struct sockaddr *)&remote, len ) == -1 ) {
		perror ( "connect" );
		exit(1);
	}

	printf ( "Connected.\n" );



	/***
	 * Prompt-loop the user, sending to the echo server and recving
	 * responses.
	 */

	while ( printf ("> "), fgets(str, BUFFSIZE, stdin), !feof(stdin) ) {

		/* This is the call to send() */
		if ( send ( s, str, strlen(str), 0 ) == -1 ) {
			perror ( "send" );
			exit(1);
		}

		/* This is the call to recv() */
		if ( (t=recv ( s, str, BUFFSIZE, 0 ) ) > 0 ) {
			str[t] = '\0';
			printf( "echo> %s", str );
		} else {
			if ( t < 0 ) {
				perror ( "recv" );
			} else {
				printf ( "Server closed connection\n");
			}
			exit (1);
		}
	}

	close(s);

	return 0;
}
