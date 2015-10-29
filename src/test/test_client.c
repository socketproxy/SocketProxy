/***
 * socketproxy/src/test/test_client.c
 * (c) 2010 Mike Doyle
 */
/*    This file is part of SocketProxy.
 *
 *    SocketProxy is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    SocketProxy is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with SocketProxy.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <strings.h>

#define DEBUG 1

int
test_socket(void)
{
    return socket ( AF_INET, SOCK_STREAM, 0 );
} /* end of test_socket */

int
test_connect(int sock)
{
    struct sockaddr_in sa;
    int t;

    bzero ( &sa, sizeof(sa) );

    sa.sin_family = AF_INET;
    sa.sin_port = htons(80);

    if ( (t = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr)) != 1 ) {
        fprintf ( stderr, "My bad. Can't inet_pton. Return code: %d\n", t);
        return -1;
    }

    return connect ( sock, (struct sockaddr *)&sa, sizeof(sa) );

} /* end of test_connect() */

int 
test_bad_connect(int sock)
{
    struct sockaddr_in sa;
    int t;

    bzero ( &sa, sizeof(sa) );

    sa.sin_family = AF_INET;
    sa.sin_port = htons(81);

    if ( (t = inet_pton(AF_INET, "127.0.0.1", &sa.sin_addr)) != 1 ) {
        fprintf ( stderr, "My bad. Can't inet_pton. Return code: %d\n", t);
        return -1;
    }

    return connect ( sock, (struct sockaddr *)&sa, sizeof(sa) );

}


int
main(void)
{

    if (DEBUG) {
        printf ( "test client Debug mode on\n");
    }

    int foo, bar, baz, qux;

    foo = test_socket();
    if (DEBUG) {
        printf ( "Return value of socket: %d\n", foo );
    }

    bar = test_connect(foo);
    if (DEBUG) {
        printf ( "Return value of connect: %d\n", bar );
    }

    baz = test_socket();
    qux = test_bad_connect(baz);
    if (DEBUG) {
        printf ( "Return value of connect: %d\n", bar );
    }



}
