/**
 * socketproxy/src/library/serialize.h
 * (c) 2010 Mike Doyle
 */

#ifndef __SP_SERIALIZE_H
#define __SP_SERIALIZE_H

#include <errno.h>
#include <stdlib.h>
#include <string.h>

typedef char *__sp_request;
typedef char *__sp_response;


/* __sp_serialize_init
 *
 * initializs an sp_serialize request or response
 */
__sp_request 
__sp_serialize_init(const char *name);



/*
 * __sp_serialize_finalize
 *
 * prepares an sp message for sending.
 */
int
__sp_serialize_finalize( __sp_request *req );



/* __sp_serialze_int
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
__sp_serialize_int( __sp_request *req, const char *name, int val );

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
__sp_serialize_str( __sp_request *req, const char *name, const char *val );



/* __sp_deserialze_int
 *
 * extract an integer from req.
 *
 * returns the deserialized int value associated with name
 *
 * uses asprintf
 */
int
__sp_deserialize_int( __sp_request *req, const char *name );



/* __sp_deserialze_str
 *
 * extract an char * from req.
 *
 * returns the deserialized int value associated with name
 *
 * uses asprintf
 */
char *
__sp_deserialize_str( __sp_request *req, const char *name );


/* __sp_serialize_destroy(__sp_request *req)
 *
 * frees the memory used by __sp_request *req
 */
void
__sp_serialize_destroy(__sp_request *req);

/* __sp_serialize_tostring(__sp_request *req)
 *
 * returns a malloced, human readable string representing req.
 *
 */
char *
__sp_serialize_tostring(__sp_request *req);


#endif
