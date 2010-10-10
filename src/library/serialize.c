/**
 * socketproxy/src/library/serialize.c
 * (c) 2010 Mike Doyle
 */

#include "serialize.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>

/* __sp_serialize_init
 *
 * initializs an sp_serialize request or response
 */
__sp_request
__sp_serialize_init(const char *name)
{
    __sp_request foo;

    asprintf( &foo, "%s\n", name );
    return foo;
} /* end of __sp_serialize_init */


/*
 * __sp_serialize_finalize
 *
 * prepares an sp message for sending.
 */
int
__sp_serialize_finalize( __sp_request *req )
{

    asprintf( req, "%s\n", *req );
    return 0;
} /* end of __sp_serialize_finalize */



/* __sp_serialize_int
 *
 * add an integer type to an __sp_request or response
 *
 * returns -1 on failure, 0 on success
 *
 * name and val are the name/value pair.
 *
 * uses asprintf
 */
int
__sp_serialize_int( __sp_request *req, const char *name, int val )
{
    asprintf(req, "%s%s: %d\n", *req, name, val);
    /*TODO: calculate the expected return value and verify against it*/
    return 0;
}

/* __sp_serialze_str
 *
 * add an char * type to an __sp_request or response
 *
 * returns -1 on failure, 0 on success
 *
 * name and val are the name/value pair.
 *
 * uses asprintf
 */
int
__sp_serialize_str( __sp_request *req, const char *name, const char *val ){
    asprintf(req, "%s%s: %s\n", *req, name, val);
    /*TODO: calculate the expected return value and verify against it*/
    return 0;
}



/* __sp_deserialze_int
 *
 * extract an integer from req.
 *
 * returns the deserialized int value associated with name
 *
 * uses asprintf
 */
int
__sp_deserialize_int( __sp_request *req, const char *name )
{
    char *tag;
    char *needle;
    char *endp; /* For strtol */
    int val;
    size_t needle_len;

    if( (needle = malloc((size_t)(strlen(name)+4))) == NULL) {
        return -1;
    }

    needle_len = asprintf( &needle, "\n%s: ", name );
    if ( (tag = strstr( *req, needle )) == NULL ) {
        free( needle );
        return -1;
    }
    free( needle );

    /* tag now points to the beginning of the line "name: value\n" This is 
     * good, but we need to get it to the beginning of value. This is why 
     * we saved the return value of asprintf
     */

    tag += needle_len;

    val = strtol ( tag, &endp, 0 );
    if ( endp == tag ) {
        return -1;
    }
    if ( *endp != '\n' ) {
        printf("Failing here (%c)\n", *endp);
        return -1;
    }
    if ( (val == LONG_MIN || val == LONG_MAX) && 
            (errno == ERANGE || errno == EINVAL) ) {
        return -1;
    }

    return val;

} /* end of __sp_deserialize_int */






/* __sp_deserialze_str
 *
 * extract an char * from req.
 *
 * returns the deserialized int value associated with name
 *
 * uses asprintf
 */
char *
__sp_deserialize_str( __sp_request *req, const char *name )
{
    char *tag;
    char *needle;
    char *endp;
    char *val;
    int val_len;
    size_t needle_len;

    if( (needle = malloc((size_t)(strlen(name)+4))) == NULL) {
        return NULL;
    }

    needle_len = asprintf( &needle, "\n%s: ", name );
    if ( (tag = strstr( *req, needle )) == NULL ) {
        free( needle );
        return NULL;
    }
    free( needle );

    /* tag now points to the beginning of the line "name: value\n" This is 
     * good, but we need to get it to the beginning of value. This is why 
     * we saved the return value of asprintf
     */

    tag += needle_len;

    if ( (endp = strchr( tag, '\n' )) == NULL ) {
        return NULL;
    }
    val_len = endp - tag;
    val = malloc ( (size_t)val_len + 1 );
    bzero ( val, val_len + 1 );
    strncpy ( val, tag, val_len + 1 );

    return val;

} /* end of __sp_deserialize_str */

/* __sp_serialize_fixate
 *
 * Completes the construction of an __sp_request.
 *
 * returns -1 on failure, 0 on success
 *
 * uses asprintf
 */
int
__sp_serialize_fixate( __sp_request *req)
{
    asprintf(req, "%s\n", *req);
    /*TODO: calculate the expected return value and verify against it*/
    return 0;
}



/* __sp_serialize_destroy(__sp_request *req)
 *
 * frees the memory used by __sp_request *req
 */
void
__sp_serialize_destroy(__sp_request *req)
{
    free (*req);
    return;
} /* end of __sp_serialize_destroy(__sp_request *req) */



/* __sp_serialize_tostring(__sp_request *req)
 *
 * returns a malloced, human readable string representing req.
 *
 */
char *
__sp_serialize_tostring(__sp_request *req)
{
    return strdup(*req);
} /* end of __sp_serialize_tostring(__sp_request *req) */
