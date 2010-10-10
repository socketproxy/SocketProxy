/***
 * socketproxy/src/test/socketpair_test.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>

int
main(void)
{
    int foo;
    int socket_vector[2];

    foo = socketpair(AF_INET,SOCK_STREAM,0,socket_vector);
    printf("Hello World!\n");
}
