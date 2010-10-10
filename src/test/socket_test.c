/***
 * socketproxy/src/test/socket_test.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>

int
main(void)
{
    int foo;
    if ( (foo = socket(AF_INET,SOCK_STREAM,0)) == -1 ){
        printf ("Socket failed. Sad.\n");
        return(1);
    }
    printf("Hello World!\n");
}
