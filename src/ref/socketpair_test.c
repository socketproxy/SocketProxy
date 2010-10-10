/**
 * socketproxy/src/ref/socketpair_test.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <sys/socket.h>

int
main(void)
{
    int socket_vector[2];

    malloc(100);
    return socketpair(AF_UNIX,SOCK_STREAM,0,socket_vector);
}
