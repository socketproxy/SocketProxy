/***
 * socketproxy/src/library/uds_client.h
 * (c) 2010 Mike Doyle
 */

#ifndef __UDS_CLIENT_H
#define __UDS_CLIENT_H

/***
 * XXX: Work in progress: replacing fifos with unix domain sockets. This
 * file will replace fifo_client.h.
 * 
 */
#include "serialize.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFSIZE 512


/* 
 * Forward declarations 
 */

/***
 * __sp_call_server -- This function takes in an __sp_request and sends
 * it to the socket proxy server process. It is usually called during
 * calls to socket and calls to read/write data.
 */
__sp_response __sp_call_server( __sp_request *req );

/* __sp_get_cmd_uds_addr()
 *
 * returns a malloc'd copy of the filepath used by the unix domain socket
 * used to to communicate with the socket proxy server process.
 */
char *__sp_get_cmd_uds_addr();

#endif
