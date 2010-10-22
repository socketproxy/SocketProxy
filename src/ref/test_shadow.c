/**
 * socketproxy/src/ref/test_shadow.c
 * (c) 2010 Mike Doyle
 */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>

int
main(void)
{
        return _socket ( AF_INET, SOCK_STREAM, 0 );
}
