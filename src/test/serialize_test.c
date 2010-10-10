/***
 * socketproxy/src/test/serialize_test.c
 * (c) 2010 Mike Doyle
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

    
