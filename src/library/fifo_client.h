/***
 * socketproxy/src/library/fifo_client.h
 * (c) 2010 Mike Doyle
 */

#ifndef __FIFO_CLIENT_H
#define __FIFO_CLIENT_H

/***
 * XXX: Work in progress: replacing fifos with unix domain sockets. This
 * will likely involve replacing this file.
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

__sp_response __sp_call_server( __sp_request *req );

/* __sp_get_cmd_fifo_name()
 *
 * returns a malloc'd copy of the filename of the fifo used to
 * communicate with he socketproxy server.
 */
char *__sp_get_cmd_fifo_name();

#endif
