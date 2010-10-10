/***
 * socketproxy/src/test/fake_socket.c
 * (c) 2010 Mike Doyle
 */

#include <sys/socket.h>
#include <stdio.h>

int
socket ( int domain, int type, int protocol )
{
    printf("Yeah.\n");
    return 0;
}
