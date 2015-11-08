/***
 * socketproxy/src/library/fifo_client.h
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

/***
 * __sp_call_server -- This function takes in an __sp_request and sends
 * it to the socket proxy server process. It is usually called during
 * calls to socket and calls to read/write data.
 */
__sp_response __sp_call_server(__sp_request *req);

/***
 * __sp_fifo_call_server -- This function takes in a char * and sends it
 * to the socket proxy server process over a fifo. It is called from
 * __sp_call_server only. It returns a malloc'd char * which must be
 * freed by the caller
 */
char *__sp_fifo_call_server(char *mesg);


/* __sp_get_cmd_fifo_name()
 *
 * returns a malloc'd copy of the filename of the fifo used to
 * communicate with he socketproxy server.
 */
char *__sp_get_cmd_fifo_name();

#endif
