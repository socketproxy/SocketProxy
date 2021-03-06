/***
 * socketproxy/src/test/serialize_test.c
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

#include "serialize.h"
#include <stdio.h>

int
main(void)
{
    __sp_request foo;
    int baz = 0;
    char *reqstr;

    foo = __sp_serialize_init("qux");
    __sp_serialize_int( &foo, "bar", 5 );
    __sp_serialize_int( &foo, "quux", 42 );
    __sp_serialize_fixate(&foo);
    baz = __sp_deserialize_int( &foo, "bar");
    reqstr = __sp_serialize_tostring( &foo );

    printf ("(%s)\n" , reqstr );

    if( baz == 5 ) {
        printf("Success!\n");
    }else{
        printf("Failure!: (%s) %d\n", foo, baz);
    }

    exit(0);
}

    
